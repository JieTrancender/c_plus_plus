#include "dispatcher_lite.h"
#include "query.pb.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

void onUnknownMessageType(const muduo::net::TcpConnectionPtr&, const MessagePtr& message, muduo::Timestamp)
{
	printf("onUnknownMessageType: %s\n", message->GetTypeName());
	// cout << ""
}

void onQuery(const muduo::net::TcpConnectionPtr&,
	const MessagePtr& message,
	muduo::Timestamp)
{
	printf("onQuery: %s\n", message->GetTypeName().c_str());
	boost::shared_ptr<muduo::Query> query(muduo::down_pointer_cast<muduo::Query>(message));
	assert(query != nullptr);
	printf("onQuery: %s %d\n", static_cast<std::string>(query->questioner()).c_str(), query->IsInitialized());
	cout << "onQuery: " << query->GetTypeName() << endl;
	cout << "onQuery: " << query->questioner() << endl;
}

// g++ dispatcher_lite_test.cpp codec.cpp query.pb.cc -lmuduo_base -lmuduo_net -lpthread -lz -lprotobuf --std=c++17
int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	ProtobufDispatcherLite dispatcher(onUnknownMessageType);
	dispatcher.registerMessageCallback(muduo::Query::descriptor(), onQuery);

	muduo::net::TcpConnectionPtr conn;
	muduo::Timestamp t;

	boost::shared_ptr<muduo::Query> query(new muduo::Query);
	query->set_id(1);
	query->set_questioner("Jie Mo");
	query->add_question("How Are You?");
	query->add_question("Hove you dinner");

	dispatcher.onProtobufMessage(conn, query, t);

	google::protobuf::ShutdownProtobufLibrary();
}