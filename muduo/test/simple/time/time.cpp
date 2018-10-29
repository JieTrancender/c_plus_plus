#include "time.h"

#include <muduo/base/Logging.h>
#include <functional>

using namespace muduo;
using namespace muduo::net;

TimeServer::TimeServer(EventLoop* loop,
	const InetAddress& listenAddr)
	: server_(loop, listenAddr, "TimeServer")
{
	server_.setConnectionCallback(std::bind(&TimeServer::onConnection, this, std::placeholders::_1));
	server_.setMessageCallback(std::bind(&TimeServer::onMessage, this, _1, _2, _3));
}

void TimeServer::start()
{
	server_.start();
}

void TimeServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "TimeServer - " << conn->peerAddress().toIpPort() << " -> "
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");

	if (conn->connected())
	{
		time_t now = ::time(nullptr);
		int32_t be32 = sockets::hostToNetwork32(static_cast<int32_t>(now));
		LOG_INFO << "send " << sizeof be32 << " " << be32;
		conn->send(&be32, sizeof be32);
		conn->shutdown();
	}
}

void TimeServer::onMessage(const TcpConnectionPtr& conn,
	Buffer* buf,
	Timestamp receiveTime)
{
	string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
		<< "data received at " << receiveTime.toString();

	conn->send(msg);
}