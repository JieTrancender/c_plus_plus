#include "echo.h"

#include <unistd.h>

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(2018);
	EchoServer server(&loop, listenAddr);

	server.start();
	loop.loop();
}