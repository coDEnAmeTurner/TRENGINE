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
