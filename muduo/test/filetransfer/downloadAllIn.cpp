#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <unistd.h>

#include <cstdio>

using namespace muduo;
using namespace muduo::net;

const char *g_file = nullptr;

string readFile(const char* fileName)
{
	string content;
	FILE *fp = ::fopen(fileName, "rb");
	if (fp)
	{
		const int kBufSize = 1024 * 1024;
		char ioBuf[kBufSize];
		::setbuffer(fp, ioBuf, sizeof ioBuf);

		char buf[kBufSize];
		size_t nRead = 0;
		while ((nRead = ::fread(buf, 1, sizeof buf, fp)) > 0)
		{
			content.append(buf, nRead);
		}
		::fclose(fp);
	}

	return content;
}

void onHighWaterMark(const TcpConnectionPtr& conn, size_t len)
{
	LOG_INFO << "HighWaterMark " << len;
}

void onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "FileServer - " << conn->peerAddress().toIpPort() << " -> "
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");

	if (conn->connected())
	{
		LOG_INFO << "FileServer - Sending file " << g_file
			<< " to " << conn->peerAddress().toIpPort();
		conn->setHighWaterMarkCallback(onHighWaterMark, 64 * 1024);
		string fileContent = readFile(g_file);
		conn->send(fileContent);
		conn->shutdown();
		LOG_INFO << "FileServer - done";
	}
}

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();
	if (argc > 1)
	{
		g_file = argv[1];

		EventLoop loop;
		InetAddress listenAddr(2018);
		TcpServer server(&loop, listenAddr, "FileServer");
		server.setConnectionCallback(onConnection);
		server.start();
		loop.loop();
	}
	else
	{
		fprintf(stderr, "Usage: %s file_for_downloading\n", argv[0]);
	}
}