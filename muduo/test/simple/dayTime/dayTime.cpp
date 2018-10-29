#include "dayTime.h"

#include <muduo/base/Logging.h>

#include <functional>

using namespace muduo;
using namespace muduo::net;

DayTimeServer::DayTimeServer(EventLoop* loop,
	const InetAddress& listenAddr)
	: server_(loop, listenAddr, "DayTimeServer")
{
	server_.setConnectionCallback(
		std::bind(&DayTimeServer::onConnection, this, _1));

	server_.setMessageCallback(
		std::bind(&DayTimeServer::onMessage, this, _1, _2, _3));
}

void DayTimeServer::start()
{
	server_.start();
}

void DayTimeServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "DayTimeServer - " << conn->peerAddress().toIpPort() << " - >"
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");

	if (conn->connected())
	{
		conn->send(Timestamp::now().toFormattedString() + '\n');
		conn->shutdown();
	}
}

void DayTimeServer::onMessage(const TcpConnectionPtr& conn,
	Buffer* buf,
	Timestamp receiveTime)
{
	string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " discards " << msg.size()
		<< " bytes received at " << receiveTime.toString();
}