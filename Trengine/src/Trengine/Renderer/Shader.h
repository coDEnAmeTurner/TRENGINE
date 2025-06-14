#pragma once
#include <memory>
#include <string>	
#include "glm/glm.hpp"

namespace Trengine {
	class Shader {
	protected:
		uint32_t rendererID;		
		std::string name;

	public:
		virtual ~Shader();

		void bind() const;
		void unBind() const;

		virtual void setUniformFloat(const std::string& name, float values) = 0;
		virtual void setUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void setUniformInt(const std::string& name, int values) = 0;
		virtual void setUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void setUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void setUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void setUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void setUniformIntArray(const std::string& name, int* values, uint32_t count) = 0;

		std::string getName() const { return name; }
		
		static Shader* create(const std::string& filepath);
	};

	class ShaderLibrary {
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
	public:
		void add(const std::shared_ptr<Shader>& shader);
		void add(const std::string& name, const std::shared_ptr<Shader>& shader);

		std::shared_ptr<Shader> load(const std::string& filepath);
		std::shared_ptr<Shader> load(const std::string& name, const std::string& filepath);

		std::shared_ptr<Shader> get(const std::string& name);

		bool exists(const std::string& name) const;

	};
}
