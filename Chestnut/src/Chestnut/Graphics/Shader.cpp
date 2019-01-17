#include "chstpch.h"
#include "Shader.h"

#include "glad\glad.h"

#include "glm\gtc\type_ptr.hpp"

#include "Chestnut\fileutils.h"

namespace chst
{
	unsigned int Shader::s_activeProgram = 0;

	unsigned int Shader::createProgram(const char* vertSrc, const char* geomSrc, const char* fragSrc)
	{
		unsigned int program = glCreateProgram();

		unsigned int vert = compileShader(GL_VERTEX_SHADER, vertSrc);
		unsigned int geom = compileShader(GL_GEOMETRY_SHADER, geomSrc);
		unsigned int frag = compileShader(GL_FRAGMENT_SHADER, fragSrc);

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

	unsigned int Shader::compileShader(unsigned int type, const char* source)
	{
		if (*source == 0)
			return 0;

		unsigned int shader = glCreateShader(type);

		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		GLint result = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			printLog(shader);
			glDeleteShader(shader);

			throw ShaderException("Compiling Error: " + std::to_string(type));
		}

		return shader;
	}

	void Shader::printLog(unsigned int object)
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

	Shader::Shader(const std::string& vs, const std::string& fs)
	{
		m_program = createProgram(readFile(vs.c_str()).c_str(), "", readFile(fs.c_str()).c_str());
	}

	Shader::Shader(const std::string& vs, const std::string& gs, const std::string& fs)
	{
		m_program = createProgram(readFile(vs.c_str()).c_str(), readFile(gs.c_str()).c_str(), readFile(fs.c_str()).c_str());
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_program);
	}

	void Shader::setUniform1i(const char* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1f(const char* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const char* name, const glm::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const char* name, const glm::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const char* name, const glm::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const char* name, const glm::mat4& matrix, bool transpose)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, transpose, glm::value_ptr(matrix));
	}

	void Shader::setUniform1i(unsigned int location, int value)
	{
		glUniform1i(location, value);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform1f(unsigned int location, float value)
	{
		glUniform1f(location, value);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform2f(unsigned int location, const glm::vec2& vector)
	{
		glUniform2f(location, vector.x, vector.y);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform3f(unsigned int location, const glm::vec3& vector)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniform4f(unsigned int location, const glm::vec4& vector)
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);

		if (glGetError() == GL_INVALID_OPERATION)
			throw ShaderException("location is an invalid uniform location .");
	}

	void Shader::setUniformMat4(unsigned int location, const glm::mat4 & matrix, bool transpose)
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
	
	unsigned int Shader::getUniformLocation(const char* name)
	{
		//glClearErrorLog();
		while (glGetError() != GL_NO_ERROR);

		GLint location = glGetUniformLocation(m_program, name);

		if (location < 0)
			throw ShaderException("unkown location for name: " + std::string(name));

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