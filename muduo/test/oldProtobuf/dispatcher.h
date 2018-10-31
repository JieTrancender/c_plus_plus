#ifndef MUDUO_TEST_PROTOBUF_DISPATCHER_H
#define MUDUO_TEST_PROTOBUF_DISPATCHER_H

#include <muduo/net/Callbacks.h>

#include <google/protobuf/message.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <map>
#include <functional>

using MessagePtr = boost::shared_ptr<google::protobuf::Message>;

class Callback : boost::noncopyable
{
public:
	// Callback(const Callback&) = delete;
	// Callback& operator=(const Callback&) = delete;

	virtual ~Callback() {};
	virtual void onMessage(const muduo::net::TcpConnectionPtr&, const MessagePtr&, muduo::Timestamp) const = 0;

private:
	// Callback(const Callback&) = default;
	// Callback& operator=(const Callback&) = default;
};

template <typename T>
class CallbackT : public Callback
{
public:
	using ProtobufMessageCallback = boost::function<void (const muduo::net::TcpConnectionPtr&,
		const boost::shared_ptr<T>&, muduo::Timestamp)>;
	// typedef boost::function<void (const muduo::net::TcpConnectionPtr&, const boost::shared_ptr<T>&, muduo::Timestamp)> ProtobufMessageCallback;

	CallbackT(const ProtobufMessageCallback& callback)
		: callback_(callback) {}

	virtual void onMessage(const muduo::net::TcpConnectionPtr& conn, const MessagePtr& message, muduo::Timestamp receiveTime) const
	{
		boost::shared_ptr<T> concrete = muduo::down_pointer_cast<T>(message);
		assert(concrete != nullptr);
		callback_(conn, concrete, receiveTime);
	}

private:
	ProtobufMessageCallback callback_;
};

class ProtobufDispatcher
{
public:
	// using ProtobufMessageCallback = std::function<void (const muduo::net:::TcpConnectionPtr&, const MessagePtr&, muduo::Timestamp)>;
	// using ProtobufMessageCallback = boost::function<void (const muduo::net::TcpConnectionPtr&, const MessagePtr&, muduo::Timestamp)>;
	typedef boost::function<void (const muduo::net::TcpConnectionPtr&, const MessagePtr&, muduo::Timestamp)> ProtobufMessageCallback;

	explicit ProtobufDispatcher(const ProtobufMessageCallback& defaultCb)
		: defaultCallback_(defaultCb) {}

	void onProtobufMessage(const muduo::net::TcpConnectionPtr& conn, const MessagePtr& message,
		muduo::Timestamp receiveTime) const
	{
		auto it = callbacks_.find(message->GetDescriptor());
		if (it != callbacks_.end())
		{
			it->second->onMessage(conn, message, receiveTime);
		}
		else
		{
			defaultCallback_(conn, message, receiveTime);
		}
	}

	template <typename T>
	void registerMessageCallback(const typename CallbackT<T>::ProtobufMessageCallback& callback)
	{
		boost::shared_ptr<CallbackT<T> > pd(new CallbackT<T>(callback));
		callbacks_[T::descriptor()] = pd;
	}

private:
	using CallbackMap = std::map<const google::protobuf::Descriptor*, boost::shared_ptr<Callback>>;

	CallbackMap callbacks_;
	ProtobufMessageCallback defaultCallback_;
};

#endif