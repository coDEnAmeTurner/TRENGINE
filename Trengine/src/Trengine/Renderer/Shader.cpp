#include "trpch.h"
#include "glad/glad.h"
#include "Trengine/Renderer/Renderer.h"
#include "Trengine/Platform/OpenGL/OpenglShader.h"

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

	Shader* Shader::create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: TR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
		}

		TR_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	void ShaderLibrary::add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->getName();
		TR_CORE_ASSERT(shaders.find(name) != shaders.end(), "Shader already exists!");
		shaders[name] = shader;
	}

	void ShaderLibrary::add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		TR_CORE_ASSERT(!exists(name), "Shader already exists!");
		shaders[name] = shader;

	}

	std::shared_ptr<Shader> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		std::shared_ptr<Shader> s;
		s.reset(shader);
		add(s);

		return s;
	}

	std::shared_ptr<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		std::shared_ptr<Shader> s;
		s.reset(shader);
		add(name, s);

		return s;
	}

	std::shared_ptr<Shader> ShaderLibrary::get(const std::string& name)
	{
		TR_CORE_ASSERT(exists(name), "Shader not found!");
		return shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return shaders.find(name) != shaders.end();
	}



}
