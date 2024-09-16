#pragma once

#include <string>	
#include "glm/glm.hpp"

namespace Trengine {
	class Shader {
	protected:
		uint32_t rendererID;
	public:
		virtual ~Shader();

		void bind() const;
		void unBind() const;
		

	};
}
