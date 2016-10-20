#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

class ChatMessage
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };

	ChatMessage() : m_body_length(0) {}

	const char* getData() const
	{
		return m_data;
	}

	char* setData()
	{
		return m_data;
	}

	std::size_t getLength() const
	{
		return header_length + m_body_length;
	}

	const char* getBody() const
	{
		return m_data + header_length;
	}

	char* setBody()
	{
		return m_data + header_length;
	}

	std::size_t getBodyLength() const
	{
		return m_body_length;
	}

	void setBodyLength(std::size_t new_length)
	{
		m_body_length = new_length;
		if (m_body_length > max_body_length)
			m_body_length = max_body_length;
	}

	bool decodeHeader()
	{
		char header[header_length + 1] = "";
		std::strncat(header, m_data, header_length);
		m_body_length = std::atoi(header);
		if (m_body_length > max_body_length)
		{
			m_body_length = 0;
			return false;
		}
		return true;
	}

	void encodeHeader()
	{
		char header[header_length + 1] = "";
		std::sprintf(header, "%4d", static_cast<int>(m_body_length));
		std::memcpy(m_data, header, header_length);
	}

private:
	char m_data[header_length + max_body_length];
	std::size_t m_body_length;
};