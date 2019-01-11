#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"

inline void glClearErrorLog()
{
	while (glGetError() != GL_NO_ERROR);
}