#include "echo.h"

#include <muduo/base/Logging.h>
#include <functional>

using namespace std::placeholders;
using namespace muduo::net;

EchoServer::EchoServer(EventLoop* loop, const InetAddress& listenAddr)
	: server_(loop, listenAddr, "EchoServer")
{
	server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, _1));
	server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, _1, _2, _3));
}

void EchoServer::start()
{
	server_.start();
	LOG_INFO << "listen: " << server_.ipPort();
}

void EchoServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");
}

void EchoServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, muduo::Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
		<< "data received at " << time.toString();

	// conn->send(msg);
	
	// 大小写互换
	for (int i = 0; i < msg.length(); ++i)
	{
		if (msg[i] >= 65 && msg[i] <= 90)
		{
			msg[i] = msg[i] + 32;
		}
		else if (msg[i] >= 97 && msg[i] <= 122)
		{
			msg[i] = msg[i] - 32;
		}
	}

	conn->send(msg);
}
