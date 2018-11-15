#include "parserobject.h"

#include <algorithm>
#include "util.h"

namespace chestnutScript
{
	using namespace chestnut2D;

	void ParserObject::parseVariable(const std::string& var)
	{		
		std::size_t posName = var.find(":");
		std::size_t posValue = var.find("=");

		std::string type = var.substr(0, posName);
		std::string name = var.substr(posName + 1, posValue - (posName + 1));
		std::string value = var.substr(posValue + 1);
		value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());

		if (stringCompare(type, "i"))
			m_variables[name] = parseInt(value);
		else if (stringCompare(type, "f"))
			m_variables[name] = parseFloat(value);
		else if (stringCompare(type, "b"))
			m_variables[name] = parseBool(value);
		else 
			m_variables[name] = value;

		m_variableNames.push_back(name);
	}

	int ParserObject::parseInt(const std::string& var)
	{
		if (var.empty())
			return 0;
		else
			return std::stoi(var);
	}

	float ParserObject::parseFloat(const std::string& var)
	{
		if (var.empty())
			return 0.0f;
		else
			return std::stof(var);
	}

	bool ParserObject::parseBool(const std::string& var)
	{
		return stringCompare("true", var);
	}

	ParserObject::ParserObject(const std::string& script)
	{
		auto lines = chestnut2D::cutString("\n", script);

		for (auto& l : lines)
		{
			parseVariable(l);
		}
	}

	std::any ParserObject::getVariable(const std::string& name)
	{
		auto var = m_variables.find(name);

		if (var != m_variables.end())
		{
			return var->second;
		}

		throw std::out_of_range("No variable \'" + name + "\' found");
	}
	
	std::vector<std::string> ParserObject::getVariableNames() const
	{
		return m_variableNames;
	}

	void ParserObject::print()
	{
		for (auto& v : m_variables)
		{
			DEBUG_MESSAGE(v.first << ": " << v.second.type().name());
		}
	}
}
