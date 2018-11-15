#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"

inline void glClearErrorLog()
{
	while (glGetError() != GL_NO_ERROR);
}