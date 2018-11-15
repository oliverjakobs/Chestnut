#pragma once

#include "gl.h"

#include "glm\glm.hpp"

#include "tools\util\stringutils.h"

#include "error\error.h"

namespace chestnut2D
{
	class Shader
	{
	private:
		GLuint m_program;

		static GLuint s_activeProgram;
	public:
		static GLuint createProgram(const char* vertSrc, const char* geomSrc, const char* fragSrc);
		static GLuint compileShader(unsigned int type, const char* source);
		static void printLog(GLuint object);

		Shader(const char* vs, const char* fs);
		Shader(const char* vs, const char* gs, const char* fs);
		~Shader();

		void setUniform1i(const GLchar* name, int value);
		void setUniform1f(const GLchar* name, float value);
		void setUniform2f(const GLchar* name, const glm::vec2& vector);
		void setUniform3f(const GLchar* name, const glm::vec3& vector);
		void setUniform4f(const GLchar* name, const glm::vec4& vector);
		void setUniformMat4(const GLchar* name, const glm::mat4& matrix, GLboolean transpose = GL_FALSE);

		void setUniform1i(GLuint location, int value);
		void setUniform1f(GLuint location, float value);
		void setUniform2f(GLuint location, const glm::vec2& vector);
		void setUniform3f(GLuint location, const glm::vec3& vector);
		void setUniform4f(GLuint location, const glm::vec4& vector);
		void setUniformMat4(GLuint location, const glm::mat4& matrix, GLboolean transpose = GL_FALSE);

		void enable() const;
		void disable() const;

		GLint getUniformLocation(const GLchar* name);
	};
}