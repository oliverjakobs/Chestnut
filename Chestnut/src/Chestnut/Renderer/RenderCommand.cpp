#include "chstpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace chst
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}