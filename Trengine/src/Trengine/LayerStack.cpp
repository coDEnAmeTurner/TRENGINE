#include "trpch.h"
#include "LayerStack.h"

namespace Trengine {
	LayerStack::LayerStack() {

	}

	LayerStack::~LayerStack() {
		for (Layer* l : layers) {
			delete l;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		if (layers.empty()) {
			layers.push_back(layer);
			layerInsertIt = layers.begin();
			return;
		}

		layerInsertIt = layers.emplace(layerInsertIt, layer);

	}

	void LayerStack::PushOverlay(Layer* overlay) {
		layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layers.erase(it);
			layerInsertIt--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		layers.erase(layers.begin());
		layerInsertIt--;
	}

}