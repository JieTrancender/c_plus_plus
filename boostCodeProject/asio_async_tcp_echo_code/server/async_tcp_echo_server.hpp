#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket) : m_socket(std::move(socket)) {}

	void start()
	{
		do_read();
	}

private:
	void do_read()
	{
		auto self(shared_from_this());
		m_socket.async_read_some(boost::asio::buffer(m_data, max_length), [this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				do_write(length);
			}
		});
	}

	void do_write(std::size_t length)
	{
		auto self(shared_from_this());
		boost::asio::async_write(m_socket, boost::asio::buffer(m_data, length),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				do_read();
			}
		});
	}

	tcp::socket m_socket;
	enum { max_length = 1024 };
	char m_data[max_length];
};

class Server
{
public:
	Server(boost::asio::io_service& io_service, short port)
		: m_acceptor(io_service, tcp::endpoint(tcp::v4(), port)), m_socket(io_service)
	{
		do_accept();
	}

private:
	void do_accept()
	{
		m_acceptor.async_accept(m_socket, [this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::make_shared<Session>(std::move(m_socket))->start();
			}

			do_accept();
		});
	}

	tcp::acceptor m_acceptor;
	tcp::socket m_socket;
};