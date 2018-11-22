#pragma once

#include <iostream>
#include <algorithm>

#ifdef _DEBUG
#define DEBUG_MESSAGE(s) {std::clog << s << "\n";}
#else
#define DEBUG_MESSAGE(s) 
#endif

#define SAFE_DELETE(ptr) if( (ptr) != nullptr ) delete (ptr); (ptr) = nullptr;


template <typename T>
const bool contains(std::vector<T>& vec, const T& elem)
{
	return (std::find(vec.begin(), vec.end(), elem) != vec.end());
}