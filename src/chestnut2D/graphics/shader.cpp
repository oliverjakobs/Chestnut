#include "shader.h"

#include "glm\gtc\type_ptr.hpp"
#include "tools\util\utils.h"

namespace chestnut2D
{
	GLuint Shader::s_activeProgram = 0;

	GLuint Shader::createProgram(const char* vertSrc, const char* geomSrc, const char* fragSrc)
	{
		GLuint program = glCreateProgram();

		GLuint vert = compileShader(GL_VERTEX_SHADER, vertSrc);
		GLuint geom = compileShader(GL_GEOMETRY_SHADER, geomSrc);
		GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragSrc);

		if (vert == 0 || frag == 0)
			throw ShaderException("Shader Missing");

		glAttachShader(program, vert);
		glAttachShader(program, geom);
		glAttachShader(program, frag);

		glLinkProgram(program);

		GLint result = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			printLog(program);
			glDeleteProgram(program);

			throw ShaderException("Linking Error");
		}

		glValidateProgram(program);

		result = GL_FALSE;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
		if (result == GL_FALSE)
		{
			printLog(program);
			glDeleteProgram(program);

			throw ShaderException("Validating Error");
		}

		glDeleteShader(vert);
		glDeleteShader(geom);
		glDeleteShader(frag);

		return program;
	}

	GLuint Shader::compileShader(unsigned int type, const char* source)
	{
		if (*source == 0)
			return 0;

		GLuint shader = glCreateShader(type);

		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		GLint result = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			printLog(shader);
			glDeleteShader(shader);

			throw ShaderException("Compiling Error: " + toString(type));
		}

		return shader;
	}

	void Shader::printLog(GLuint object)
	{
		GLint log_length = 0;
		if (glIsShader(object))
			glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
		else if (glIsProgram(object))
			glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
		else
		{
			fprintf(stderr, "printlog: Not a shader or a program\n");
			return;
		}

		char* log = (char*)malloc(log_length);

		if (glIsShader(object))
			glGetShaderInfoLog(object, log_length, NULL, log);
		else if (glIsProgram(object))
			glGetProgramInfoLog(object, log_length, NULL, log);

		fprintf(stderr, "%s", log);
		free(log);
	}

	Shader::Shader(const char* vs, const char* fs)
	{
		m_program = createProgram(vs, "", fs);
	}

	Shader::Shader(const char* vs, const char* gs, const char* fs)
	{
		m_program = createProgram(vs, gs, fs);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_program);
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix, GLboolean transpose)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, transpose, glm::value_ptr(matrix));
	}

	void Shader::setUniform1i(GLuint location, int value)
	{
		glUniform1i(location, value);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform1f(GLuint location, float value)
	{
		glUniform1f(location, value);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform2f(GLuint location, const glm::vec2& vector)
	{
		glUniform2f(location, vector.x, vector.y);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform3f(GLuint location, const glm::vec3& vector)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform4f(GLuint location, const glm::vec4& vector)
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniformMat4(GLuint location, const glm::mat4 & matrix, GLboolean transpose)
	{
		glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(matrix));

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::enable() const
	{
		if (m_program != s_activeProgram)
			glUseProgram(m_program);

		s_activeProgram = m_program;
	}

	void Shader::disable() const
	{
		glUseProgram(0);

		if (m_program == s_activeProgram)
			s_activeProgram = 0;
	}
	
	GLint Shader::getUniformLocation(const GLchar* name)
	{
		glClearErrorLog();

		GLint location = glGetUniformLocation(m_program, name);

		GLenum error = glGetError();

		if (error == GL_INVALID_VALUE)
		{
			throw ShaderException("program is not a value generated by OpenGL");
		}
		else if (error == GL_INVALID_OPERATION)
		{
			throw ShaderException("program is not a program object or has not been successfully linked.");
		}

		return location;
	}
}