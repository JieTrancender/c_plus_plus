#include "dispatcher.h"
#include "query.pb.h"

#include <iostream>
#include <iostream>

using std::cout;
using std::endl;

using QueryPtr = boost::shared_ptr<muduo::Query>;
using AnswerPtr = boost::shared_ptr<muduo::Answer>;

void test_down_pointer_cast()
{
	::boost::shared_ptr<google::protobuf::Message> msg(new muduo::Query);
	::boost::shared_ptr<muduo::Query> query(muduo::down_pointer_cast<muduo::Query>(msg));
	assert(msg && query);

	if (!query)
	{
		abort();
	}
}

void onQuery(const muduo::net::TcpConnectionPtr&, const QueryPtr& message, muduo::Timestamp)
{
	cout << "onQuery: " << message->GetTypeName() << endl;
}

void onAnswer(const muduo::net::TcpConnectionPtr&, const AnswerPtr& message, muduo::Timestamp)
{
	cout << "onAnswer: " << message->GetTypeName() << endl;
}

void onUnknownMessageType(const muduo::net::TcpConnectionPtr&, const MessagePtr& message, muduo::Timestamp)
{
	cout << "onUnknownMessageType: " << message->GetTypeName() << endl;
}

// g++ dispatcher_test.cpp codec.cpp query.pb.cc -lmuduo_base -lmuduo_net -lpthread -lprotobuf -lz --std=c++17
int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	test_down_pointer_cast();

	ProtobufDispatcher dispatcher(onUnknownMessageType);
	dispatcher.registerMessageCallback<muduo::Query>(onQuery);
	dispatcher.registerMessageCallback<muduo::Answer>(onAnswer);

	muduo::net::TcpConnectionPtr conn;
	muduo::Timestamp t;

	boost::shared_ptr<muduo::Query> query(new muduo::Query);
	boost::shared_ptr<muduo::Answer> answer(new muduo::Answer);
	boost::shared_ptr<muduo::Empty> empty(new muduo::Empty);

	// query->set_id(1);
	// query->set_questioner("Jie Mo");
	// query->add_question("How are you?");

	// answer->set_id(2);
	// answer->set_questioner("Jie Moe");
	// answer->set_answerer("Jing Luo");
	// answer->add_solution("I am fine.");

	// empty->set_id(3);

	dispatcher.onProtobufMessage(conn, query, t);
	dispatcher.onProtobufMessage(conn, answer, t);
	dispatcher.onProtobufMessage(conn, empty, t);

	google::protobuf::ShutdownProtobufLibrary();
}