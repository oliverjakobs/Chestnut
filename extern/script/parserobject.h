#pragma once

#include <map>
#include <any>
#include <vector>

namespace chestnutScript
{
	class ParserException : public std::exception 
	{
	private:
		std::string m_msg;

	public:
		ParserException(const std::string& msg) : m_msg(msg) {}

		const char* what() const throw ()
		{
			return m_msg.c_str();
		}
	};

	class ParserObject
	{
	private:
		std::vector<std::string> m_variableNames;
		std::map<std::string, std::any> m_variables;

		void parseVariable(const std::string& var);

		int parseInt(const std::string& var);
		float parseFloat(const std::string& var);
		bool parseBool(const std::string& var);
		//glm::vec2 parseVec2(const std::string& var);
	public:
		ParserObject(const std::string& script);

		std::any getVariable(const std::string& name);

		template <typename T>
		T getVariable(const std::string& name);

		std::vector<std::string> getVariableNames() const;

		void print();
	};

	template<typename T>
	inline T ParserObject::getVariable(const std::string& name)
	{
		try
		{
			return std::any_cast<T>(m_variables.at(name));
		}
		catch (std::bad_any_cast&)
		{
			throw ParserException("Variable (" + name + ") and type not matching");
		}
		catch (std::out_of_range&)
		{
			throw ParserException("No variable \'" + name + "\' found");
		}
	}
}