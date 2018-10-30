#pragma once

#include <muduo/net/TcpServer.h>

#include <boost/circular_buffer.hpp>

#include <unordered_set>

class EchoServer
{
public:
	EchoServer(muduo::net::EventLoop* loop,
		const muduo::net::InetAddress& listenAddr,
		int idleSeconds);

	void start();

private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	void onMessage(const muduo::net::TcpConnectionPtr& conn,
		muduo::net::Buffer* buf,
		muduo::Timestamp receiveTime);

	void onTimer();

	void dumpConnectionBuckets() const;

	using WeakTcpConnectionPtr = std::weak_ptr<muduo::net::TcpConnection>;

	struct Entry : public muduo::copyable
	{
		explicit Entry(const WeakTcpConnectionPtr& weakConn)
			: weakConn_(weakConn)
		{}

		~Entry()
		{
			muduo::net::TcpConnectionPtr conn = weakConn_.lock();
			if (conn)
			{
				conn->shutdown();
			}
		}

		WeakTcpConnectionPtr weakConn_;
	};

	using EntryPtr = std::shared_ptr<Entry>;
	using WeakEntryPtr = std::weak_ptr<Entry>;
	using Bucket = std::unordered_set<EntryPtr>;
	using WeakConnectionList = boost::circular_buffer<Bucket>;

	muduo::net::TcpServer server_;
	WeakConnectionList connectionBuckets_;
};