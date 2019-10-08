#pragma once

#include <functional>

#define BIT(x) (1 << x)

#define BIND_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

#define SAFE_DELETE(ptr) if( (ptr) != nullptr ) delete (ptr); (ptr) = nullptr;