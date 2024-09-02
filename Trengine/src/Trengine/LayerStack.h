#pragma once

#include "Trengine/Core.h"
#include "Layer.h"	
#include <vector>

namespace Trengine {
	class TR_API LayerStack {
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsertIt;
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	};
}