#include "trpch.h"
#include "OpenglShader.h"
#include "glad/glad.h"
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"

namespace Trengine {
	std::string OpenGLShader::readFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();

		}
		else {
			TR_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	GLenum OpenGLShader::shaderTypeFromString(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		TR_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& source) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			TR_CORE_ASSERT(eol != std::string::npos, "Syntex error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			TR_CORE_ASSERT(shaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[shaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		GLuint program = glCreateProgram();

		for (auto& kv : shaderSources) {
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				TR_CORE_ERROR("{0}", infoLog.data());
				TR_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			shaderIDs.push_back(shader);

		}

		rendererID = program;

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			for (auto& s : shaderIDs) {
				glDetachShader(program, s);
			}

			glDeleteProgram(program);

			for (auto& s : shaderIDs) {
				glDeleteShader(s);
			}

			TR_CORE_ERROR("{0}", infoLog.data());
			TR_CORE_ASSERT(false, "Shader link failure!");
			return;

		}

	}

	std::string OpenGLShader::extractName(std::string filepath)
	{
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		return filepath.substr(lastSlash, count);
		
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		this->name = name;
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string src = readFile(filepath);
		auto shaderSources = preProcess(src);
		compile(shaderSources);

		name = extractName(filepath);
	}

	void OpenGLShader::setUniformInt(const std::string& name, int values) {
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1i(location, values);
	}

	void OpenGLShader::setUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1iv(location, count, values);

	}

	void OpenGLShader::setUniformFloat(const std::string& name, float values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, values);
	}

	void OpenGLShader::setUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::setUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::setUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::setUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(matrix));
	}

	void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		bind();
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}


