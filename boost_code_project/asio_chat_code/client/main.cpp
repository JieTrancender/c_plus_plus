// asio_chat_client.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"

#include <iostream>
#include "asio_client.hpp"

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
		ChatClient client(io_service, endpoint_iterator);

		std::thread t([&io_service]()
		{
			io_service.run();
		});

		char line[ChatMessage::max_body_length + 1];
		while (std::cin.getline(line, ChatMessage::max_body_length + 1))
		{
			ChatMessage msg;
			msg.setBodyLength(std::strlen(line));
			std::memcpy(msg.setBody(), line, msg.getBodyLength());
			msg.encodeHeader();
			client.write(msg);
		}

		client.close();
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

    return 0;
}

