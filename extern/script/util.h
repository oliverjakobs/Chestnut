#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace chestnut2D
{
	inline bool stringCompare(const std::string& s1, const std::string& s2)
	{
		return s1.compare(s2) == 0;
	}

	inline std::vector<std::string> cutString(const std::string& c, const std::string& string)
	{
		std::string rest = string;
		std::vector<std::string> lines;

		for (std::size_t pos = rest.find(c); pos != std::string::npos; pos = rest.find(c))
		{
			std::string line = rest.substr(0, pos);
			rest = rest.substr(pos + c.length());

			if (!line.empty())
				lines.push_back(line);
		}

		if (!rest.empty())
			lines.push_back(rest);

		return lines;
	}

	inline std::vector<std::string> cutStringBefore(const std::string& c, const std::string& string)
	{
		std::string rest = string;
		std::vector<std::string> lines;

		for (std::size_t pos = rest.find(c); pos != std::string::npos; pos = rest.find(c, c.length()))
		{
			std::string line = rest.substr(0, pos);
			rest = rest.substr(pos);

			if (!line.empty())
				lines.push_back(line);
		}

		if (!rest.empty())
			lines.push_back(rest);

		return lines;
	}

	inline std::vector<std::size_t> findStrings(const std::string& str, std::vector<std::string> strings)
	{
		std::vector<std::size_t> pos;

		for (auto s : strings)
		{
			pos.push_back(str.find(s));
		}

		return pos;
	}

#define SAFE_DELETE(ptr) if( (ptr) != nullptr ) delete (ptr); (ptr) = nullptr;

#ifdef _DEBUG
#define DEBUG_MESSAGE(s) {std::clog << s << "\n";}
#else
#define DEBUG_MESSAGE(s) 
#endif

#define ERROR_MESSAGE(e, s) {std::cerr << "[" << e << "-ERROR] " << s << "\n";}

	template <typename T>
	std::string to_string(T value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}

	template< typename... argv >
	std::string stringf(const char* format, argv... args) 
	{
		const size_t SIZE = std::snprintf(NULL, 0, format, args...);

		std::string output;
		output.resize(SIZE + 1);
		std::snprintf(&(output[0]), SIZE + 1, format, args...);
		return std::move(output);
	}

#define CLAMP_VEC(v,m) { if (v.get_length() > m) {v.normalize(); v*= m;}}
#define CLAMP(a,b,c) { b = ((b) < (a))? (a) : (((b) > (c))? (c): (b));}

#define DEG_TO_RAD(a) (a * M_PI / 180.0)
#define RAD_TO_DEG(a) (a * 180.0 / M_PI) 
}