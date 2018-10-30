#include "codec.hpp"

#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <unistd.h>

#include <cstdio>

#include <set>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

class ChatServer : noncopyable
{
public:
	ChatServer(EventLoop* loop,
		const InetAddress& listenAddr,
		int maxConnections = 2)
	: server_(loop, listenAddr, "ChatServer"),
	  codec_(std::bind(&ChatServer::onStringMessage, this, _1, _2, _3)),
	  connections_(new ConnectionList),
	  kMaxConnections_(maxConnections),
	  numConnected_(0)
	{
		server_.setConnectionCallback(
			std::bind(&ChatServer::onConnection, this, _1));
		server_.setMessageCallback(
			std::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
	}

	void setThreadNum(int numThreads)
	{
		server_.setThreadNum(numThreads);
	}

	void start()
	{
		server_.start();
	}

private:
	using ConnectionList = std::set<TcpConnectionPtr>;
	using ConnectionListPtr = std::shared_ptr<ConnectionList>;

	void onConnection(const TcpConnectionPtr& conn)
	{
		LOG_INFO << "ChatServer - " << conn->peerAddress().toIpPort() << " -> "
			<< conn->localAddress().toIpPort() << " is "
			<< (conn->connected() ? "UP" : "DOWN");

		MutexLockGuard lock(mutex_);
		if (!connections_.unique())
		{
			connections_.reset(new ConnectionList(*connections_));
		}
		assert(connections_.unique());

		if (conn->connected())
		{
			++numConnected_;
			if (numConnected_ > kMaxConnections_)
			{
				conn->shutdown();
				conn->forceCloseWithDelay(3.0);
			}

			connections_->insert(conn);
		}
		else
		{
			--numConnected_;
			connections_->erase(conn);
		}
		LOG_INFO << "numConnected = " << numConnected_;
	}

	void onStringMessage(const TcpConnectionPtr&,
		const string& message,
		Timestamp)
	{
		ConnectionListPtr connections = getConnectionList();
		for (auto it = connections->begin();
			it != connections->end();
			++it)
		{
			codec_.send(get_pointer(*it), message);
		}
		// for (auto &it : connections)
		// {
		// 	codec_.send(get_pointer(it), message);
		// }
	}

	ConnectionListPtr getConnectionList()
	{
		MutexLockGuard lock(mutex_);
		return connections_;
	}

	
	TcpServer server_;
	LengthHeaderCodec codec_;
	ConnectionListPtr connections_;
	MutexLock mutex_;
	int numConnected_;
	const int kMaxConnections_;
};

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();
	if (argc > 1)
	{
		EventLoop loop;
		uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
		InetAddress listenAddr(port);
		ChatServer server(&loop, listenAddr);
		if (argc > 2)
		{
			server.setThreadNum(atoi(argv[2]));
		}
		server.start();
		loop.loop();
	}
	else
	{
		fprintf(stderr, "Usage: %s port [threadNum]\n", argv[0]);
	}
}