#include "codec.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <functional>
#include <map>
#include <set>
#include <any>
#include <atomic>

#include <cstdio>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

namespace pubsub
{

using ConnectionSubscription = std::set<string>;

class Topic : public muduo::copyable
{
public:
	Topic(const string& topic)
		:topic_(topic) {}

	void add(const TcpConnectionPtr& conn)
	{
		audiences_.insert(conn);
		if (lastPubTime_.valid())
		{
			conn->send(makeMessage());
		}
	}

	void remove(const TcpConnectionPtr& conn)
	{
		audiences_.erase(conn);
	}

	void publish(const string& content, Timestamp time)
	{
		content_ = content;
		lastPubTime_ = time;
		string message = makeMessage();
		for (const auto& it : audiences_)
		{
			(*it).send(message);
		}
	}

private:
	string makeMessage()
	{
		return "pub " + topic_ + "\r\n" + content_ + "\r\n";
	}

	string topic_;
	string content_;
	Timestamp lastPubTime_;
	std::set<TcpConnectionPtr> audiences_;
};

class PubSubServer : boost::noncopyable
{
public:
	PubSubServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr, int maxConnections)
		:loop_(loop), server_(loop, listenAddr, "PubSubServer"), kMaxConnections_(maxConnections), numConnected_(0)
	{
		server_.setConnectionCallback(std::bind(&PubSubServer::onConnection, this, _1));
		server_.setMessageCallback(std::bind(&PubSubServer::onMessage, this, _1, _2, _3));
		loop_->runEvery(1.0, std::bind(&PubSubServer::timePublish, this));
	}

	void start()
	{
		server_.start();
	}

private:
	void onConnection(const TcpConnectionPtr& conn)
	{
		LOG_INFO << "PubSubServer - " << conn->peerAddress().toIpPort() << " -> "
			<< conn->localAddress().toIpPort() << " is "
			<< (conn->connected() ? "UP" : "DOWN");

		if (conn->connected())
		{
			conn->setContext(ConnectionSubscription());

			++numConnected_;
			if (numConnected_ > kMaxConnections_)
			{
				conn->shutdown();
				conn->forceCloseWithDelay(3.0);
			}
		}
		else
		{
			--numConnected_;

			const ConnectionSubscription& connSub = boost::any_cast<const ConnectionSubscription&>(conn->getContext());
			// const ConnectionSubscription& connSub = std::any_cast<const ConnectionSubscription&>(conn->getContext());
			for (const auto& it : connSub)
			{
				doUnsubscribe(conn, it);
			}
		}

		LOG_INFO << "numConnected = " << numConnected_;
	}

	void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime)
	{
		ParseResult result = kSuccess;
		while (result == kSuccess)
		{
			string cmd;
			string topic;
			string content;
			result = parseMessage(buf, &cmd, &topic, &content);
			if (result == kSuccess)
			{
				if (cmd == "pub")
				{
					LOG_INFO <<  conn->name() << " pub " << topic;
					doPublish(conn->name(), topic, content, receiveTime);
				}
				else if (cmd == "sub")
				{
					LOG_INFO << conn->name() << " subscribes " << topic;
					doSubscribe(conn, topic);
				}
				else if (cmd == "unsub")
				{
					doUnsubscribe(conn, topic);
				}
				else
				{
					conn->shutdown();
					result = kError;
				}
			}
			else if (result == kError)
			{
				conn->shutdown();
			}
		}
	}

	void timePublish()
	{
		Timestamp now = Timestamp::now();
		doPublish("internal", "utc_time", now.toFormattedString(), now);
	}

	// boost::any& TcpConnection::getContext() const
	void doSubscribe(const TcpConnectionPtr& conn, const string& topic)
	{
		LOG_INFO << conn->name() << " doSubscribe " << topic;
		// ConnectionSubscription *connSub = std::any_cast<ConnectionSubscription*>(conn->getMutableContext());
		// connSub->insert(topic);
		// getTopic(topic).add(conn);

		ConnectionSubscription* connSub = boost::any_cast<ConnectionSubscription>(conn->getMutableContext());
	    connSub->insert(topic);
	    getTopic(topic).add(conn);
	}

	void doUnsubscribe(const TcpConnectionPtr& conn, const string& topic)
	{
		LOG_INFO << conn->name() << " unsubscribes " << topic;
		// getTopic(topic).remove(conn);
		// ConnectionSubscription *connSub = std::any_cast<ConnectionSubscription*>(conn->getMutableContext());
		// connSub->erase(topic);

		// topic could be the one to be destroyed, so don't use it after erasing.
		getTopic(topic).remove(conn);
	    ConnectionSubscription* connSub = boost::any_cast<ConnectionSubscription>(conn->getMutableContext());
	    connSub->erase(topic);
	}

	void doPublish(const string& source, const string& topic, const string& content, Timestamp time)
	{
		LOG_INFO << source << " doPublish " << topic << " " << content;
		getTopic(topic).publish(content, time);
	}

	Topic& getTopic(const string& topic)
	{
		auto it = topics_.find(topic);
		if (it == topics_.end())
		{
			LOG_INFO << " topics_.insert " << topic;
			it = topics_.insert(std::make_pair(topic, Topic(topic))).first;
		}

		return it->second;
	}

	EventLoop *loop_;
	TcpServer server_;
	std::map<string, Topic> topics_;
	std::atomic_int numConnected_;
	const int kMaxConnections_;
};

}

// g++ -o hub hub.cpp codec.cpp -lmuduo_base -lmuduo_net -lpthread --std=c++17
int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
		EventLoop loop;
		if (argc > 3)
		{

		}

		pubsub::PubSubServer server(&loop, InetAddress(port), atoi(argv[2]));
		server.start();
		loop.loop();
	}
	else
	{
		printf("Usage: %s pubsub_port maxConnections [inspect_port]\n", argv[0]);
	}
}