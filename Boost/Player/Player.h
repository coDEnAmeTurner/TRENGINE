#pragma once


#include "../Color/Color.h"
#include "../Random/Random.h"

#include "../ParticleSystem/ParticleSystem.h"

namespace Trengine {
	class Player
	{
	public:
		Player();

		void loadAssets();

		void onUpdate(Timestep ts);
		void onRender();

		void onImGuiRender();

		void reset();

		float getRotation() { return velocity.y * 4.0f - 90.0f; }
		const glm::vec2& getPosition() const { return position; }

		uint32_t getScore() const { return (uint32_t)(position.x + 10.0f) / 10.0f; }
	private:
		glm::vec2 position = { -10.0f, 0.0f };
		glm::vec2 velocity = { 5.0f, 0.0f };

		float enginePower = 0.5f;
		float gravity = 0.4f;

		float time = 0.0f;
		float smokeEmitInterval = 0.4f;
		float smokeNextEmitTime = smokeEmitInterval;

		ParticleProps smokeParticle, engineParticle;
		ParticleSystem particleSystem;

		std::shared_ptr <Texture2D> shipTexture;
	};
}