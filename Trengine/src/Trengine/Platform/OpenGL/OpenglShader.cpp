#include "trpch.h"
#include "OpenglShader.h"
#include "glad/glad.h"
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"

namespace Trengine {
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxlength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxlength);

			std::vector<GLchar> infoLog(maxlength);
			glGetShaderInfoLog(vertexShader, maxlength, &maxlength, &infoLog[0]);

			glDeleteShader(vertexShader);

			TR_CORE_ERROR("{0}", infoLog.data());
			TR_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return;

		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxlength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxlength);

			std::vector<GLchar> infoLog(maxlength);
			glGetShaderInfoLog(fragmentShader, maxlength, &maxlength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			TR_CORE_ERROR("{0}", infoLog.data());
			TR_CORE_ASSERT(false, "Fragment shader compilation failure!");

			return;

		}

		rendererID = glCreateProgram();
		GLuint program = rendererID;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			TR_CORE_ERROR("{0}", infoLog.data());
			TR_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	void OpenGLShader::uploadUniformFloat(const std::string& name, float values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, values);
	}

	void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}


