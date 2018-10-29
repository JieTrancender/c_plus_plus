#include "time.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();

	EventLoop loop;
	InetAddress listenAddr(2018);
	TimeServer server(&loop, listenAddr);
	server.start();
	loop.loop();
}
