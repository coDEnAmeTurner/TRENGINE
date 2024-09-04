#pragma once
#include "Trengine/Core.h"
#include "Trengine/Layer.h"

namespace Trengine {
	class TR_API ImGUILayer : public Layer {
	private:
		float time = 0.0f;
	public:
		ImGUILayer();
		~ImGUILayer();

	};

}