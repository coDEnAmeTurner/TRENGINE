#include "trpch.h"
#include "Shader.h"
#include "glad/glad.h"

namespace Trengine {
	

	Shader::~Shader()
	{
		glDeleteProgram(rendererID);
	}

	void Shader::bind() const
	{
		glUseProgram(rendererID);
	}

	void Shader::unBind() const
	{
		glUseProgram(0);
	}

}
