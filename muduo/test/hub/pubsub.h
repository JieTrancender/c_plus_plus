#ifndef MUDUO_TEST_HUB_PUBSUB_H
#define MUDUO_TEST_HUB_PUBSUB_H

#include <muduo/net/TcpClient.h>

#include <functional>

namespace pubsub
{

using muduo::string;
using muduo::Timestamp;

class PubSubClient : boost::noncopyable
{
public:
	using ConnectionCallback = std::function<void (PubSubClient*)>;
	using SubscribeCallback = std::function<void (const string& topic, const string& content, Timestamp)>;

	PubSubClient(muduo::net::EventLoop* loop, const muduo::net::InetAddress& hubAddr, const string& name);
	void start();
	void stop();
	bool connected() const;

	void setConnectionCallback(const ConnectionCallback& callback)
	{
		connectionCallback_ = callback;
	}

	bool subscribe(const string& topic, const SubscribeCallback& callback);
	void unsubscribe(const string& topic);
	bool publish(const string& topic, const string& content);

private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);
	void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp receiveTime);
	bool send(const string& message);

	muduo::net::TcpClient client_;
	muduo::net::TcpConnectionPtr conn_;
	ConnectionCallback connectionCallback_;
	SubscribeCallback subscribeCallback_;
};

}

#endif