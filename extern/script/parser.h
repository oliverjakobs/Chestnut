#pragma once

#include "fileutils.h"
#include "parserobject.h"

namespace chestnutScript
{
	class Parser
	{
	protected:
		std::map<std::string, ParserObject*> m_objects;

	public:
		std::string processString(const std::string& str);

		ParserObject* getObject(const std::string& name) const;

		void loadObjects(const std::string& script);

		void print() const;
	};
}