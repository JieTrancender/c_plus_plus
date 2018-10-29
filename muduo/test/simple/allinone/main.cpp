#include "../chargen/chargen.h"
#include "../dayTime/dayTime.h"
#include "../echo/echo.h"
#include "../time/time.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();
	EventLoop loop;

	ChargenServer chargenServer(&loop, InetAddress(2010));
	chargenServer.start();

	DayTimeServer dayTimeServer(&loop, InetAddress(2011));
	dayTimeServer.start();

	EchoServer echoServer(&loop, InetAddress(2012));
	echoServer.start();

	TimeServer timeServer(&loop, InetAddress(2013));
	timeServer.start();

	loop.loop();
}