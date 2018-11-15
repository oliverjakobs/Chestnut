#include "parser.h"

#include <algorithm>

namespace chestnutScript
{
	using namespace chestnut2D;

	std::string Parser::processString(const std::string& str)
	{
		std::string processed = str;

		std::size_t start = processed.find("#");
		std::size_t end = processed.find("\n", start);

		while (start != std::string::npos)
		{
			processed.erase(start, end - start);

			start = processed.find("#");
			end = processed.find("\n", start);
		}

		processed.erase(std::remove(processed.begin(), processed.end(), ' '), processed.end());

		return processed;
	}

	ParserObject* Parser::getObject(const std::string& name) const
	{
		try
		{
			return m_objects.at(name);
		}
		catch (std::out_of_range&)
		{
			return nullptr;
		}
	}

	void Parser::loadObjects(const std::string& script)
	{
		std::string name;
		std::size_t namePos;
		std::size_t nameLength;

		std::string object;
		std::string rest = processString(script);

		namePos = rest.find("[");
		nameLength = rest.find("]") - namePos;

		while (namePos != rest.npos)
		{
			name = rest.substr(namePos + 1, nameLength - 1);
			rest = rest.substr(namePos + nameLength + 1);

			namePos = rest.find("[");
			nameLength = rest.find("]") - namePos;

			object = rest.substr(0, namePos);

			m_objects[name] = new ParserObject(object);
		} 
	}

	void Parser::print() const
	{
		for (auto& o : m_objects)
		{
			DEBUG_MESSAGE(o.first);
			o.second->print();
			DEBUG_MESSAGE("");
		}
	}
}
