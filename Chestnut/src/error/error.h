#pragma once

#include <exception>
#include <string.h>

namespace chst
{
	class ParserException : public std::exception
	{
	private:
		std::string m_msg;
	public:
		ParserException(const std::string& msg)
		{
			m_msg = msg;
		}

		virtual const char* what() const throw()
		{
			return m_msg.c_str();
		}
	};

	class ShaderException : public std::exception
	{
	private:
		std::string m_msg;
	public:
		ShaderException(const std::string& shader)
		{
			m_msg = "Shader Exception: " + shader;
		}

		virtual const char* what() const throw()
		{
			return m_msg.c_str();
		}
	};
}