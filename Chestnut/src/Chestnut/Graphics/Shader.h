#pragma once

#include "api.h"
#include "chstpch.h"

#include "glm\glm.hpp"

namespace chst
{
	class CHESTNUT_API ShaderException : public std::exception
	{
	private:
		std::string m_msg;
	public:
		ShaderException(const std::string& shader)
		{
			m_msg = "Shader Exception: " + shader;
		}

		virtual const char* what() const throw()
		{
			return m_msg.c_str();
		}
	};

	class CHESTNUT_API Shader
	{
	private:
		unsigned int m_program;

		static unsigned int s_activeProgram;
	public:
		// shader creation
		static unsigned int createProgram(const char* vertSrc, const char* geomSrc, const char* fragSrc);
		static unsigned int compileShader(unsigned int type, const char* source);
		static void printLog(unsigned int object);

		Shader(const std::string& vs, const std::string& fs);
		Shader(const std::string& vs, const std::string& gs, const std::string& fs);
		~Shader();

		void setUniform1i(const char* name, int value);
		void setUniform1f(const char* name, float value);
		void setUniform2f(const char* name, const glm::vec2& vector);
		void setUniform3f(const char* name, const glm::vec3& vector);
		void setUniform4f(const char* name, const glm::vec4& vector);
		void setUniformMat4(const char* name, const glm::mat4& matrix, bool transpose = false);

		void setUniform1i(unsigned int location, int value);
		void setUniform1f(unsigned int location, float value);
		void setUniform2f(unsigned int location, const glm::vec2& vector);
		void setUniform3f(unsigned int location, const glm::vec3& vector);
		void setUniform4f(unsigned int location, const glm::vec4& vector);
		void setUniformMat4(unsigned int location, const glm::mat4& matrix, bool transpose = false);

		void enable() const;
		void disable() const;

		unsigned int getUniformLocation(const char* name);
	};
}