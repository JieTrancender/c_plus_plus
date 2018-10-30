#include "../Buffer.h"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
// #include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

using muduo::string;
using muduo::net::Buffer;

BOOST_AUTO_TEST_CASE(testBufferAppendRetrieve)
{
	Buffer buf;
	BOOST_CHECK_EQUAL(buf.readableBytes(), 0);
	BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize);
	BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend);
}