#pragma once
#include "../Random/Random.h"
#include "Trengine/Core/Timestep.h"
#include "Trengine/Renderer/Renderer2D.h"

namespace Trengine {
	struct ParticleProps
	{
		glm::vec2 position;
		glm::vec2 velocity, velocityVariation;
		glm::vec4 colorBegin, colorEnd;
		float sizeBegin, sizeEnd, sizeVariation;
		float lifeTime = 1.0f;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem();

		void emit(const ParticleProps& particleProps);

		void onUpdate(Timestep ts);
		void onRender();
	private:
		struct Particle
		{
			glm::vec2 position;
			glm::vec2 velocity;
			glm::vec4 colorBegin, colorEnd;
			float rotation = 0.0f;
			float sizeBegin, sizeEnd;

			float lifeTime = 1.0f;
			float lifeRemaining= 0.0f;

			bool active = false;
		};
		std::vector<Particle> particlePool;
		uint32_t poolIndex = 999;
	};
}