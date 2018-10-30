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
		const InetAddress& listenAddr)
	: server_(loop, listenAddr, "ChatServer"),
	  codec_(std::bind(&ChatServer::onStringMessage, this, _1, _2, _3))
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
	void onConnection(const TcpConnectionPtr& conn)
	{
		LOG_INFO << "ChatServer - " << conn->peerAddress().toIpPort() << " -> "
			<< conn->localAddress().toIpPort() << " is "
			<< (conn->connected() ? "UP" : "DOWN");

		MutexLockGuard lock(mutex_);
		if (conn->connected())
		{
			connections_.insert(conn);
		}
		else
		{
			connections_.erase(conn);
		}
	}

	void onStringMessage(const TcpConnectionPtr&,
		const string& message,
		Timestamp)
	{
		MutexLockGuard lock(mutex_);
		for (auto &it : connections_)
		{
			codec_.send(get_pointer(it), message);
		}
	}

	using ConnectionList = std::set<TcpConnectionPtr>;
	TcpServer server_;
	LengthHeaderCodec codec_;
	ConnectionList connections_;
	MutexLock mutex_;
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