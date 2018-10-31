#ifndef MUDUO_TEST_PROTOBUF_DISPATCHER_LITE_H
#define MUDUO_TEST_PROTOBUF_DISPATCHER_LITE_H

#include <muduo/net/Callbacks.h>

#include <google/protobuf/message.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <map>

using MessagePtr = boost::shared_ptr<google::protobuf::Message>;

class ProtobufDispatcherLite : boost::noncopyable
{
public:
	using ProtobufMessageCallback = boost::function<void (const muduo::net::TcpConnectionPtr&, const MessagePtr&, muduo::Timestamp)>;

	explicit ProtobufDispatcherLite(const ProtobufMessageCallback& defaultCb)
		: defaultMessageCallback_(defaultCb) {}

	void onProtobufMessage(const muduo::net::TcpConnectionPtr& conn, const MessagePtr& message, muduo::Timestamp receiveTime) const
	{
		auto it = callbacks_.find(message->GetDescriptor());
		if (it != callbacks_.end())
		{
			it->second(conn, message, receiveTime);
		}
		else
		{
			defaultMessageCallback_(conn, message, receiveTime);
		}
	}

	void registerMessageCallback(const google::protobuf::Descriptor* descriptor, const ProtobufMessageCallback& callback)
	{
		callbacks_[descriptor] = callback;
	}

private:
	using CallbackMap = std::map<const google::protobuf::Descriptor*, ProtobufMessageCallback>;
	CallbackMap callbacks_;
	ProtobufMessageCallback defaultMessageCallback_;
};

#endif