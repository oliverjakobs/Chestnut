#pragma once

#include <string>
#include <fstream>
#include "util.h"

namespace chestnut2D
{
	inline std::string read_file(const char* filepath)
	{
		if (filepath == nullptr)
			return "";

		if (*filepath == 0)
			return "";

		std::ifstream ifs(filepath);

		std::string content(std::istreambuf_iterator<char>(ifs.rdbuf()), std::istreambuf_iterator<char>());
		
		return content;
 	}
}