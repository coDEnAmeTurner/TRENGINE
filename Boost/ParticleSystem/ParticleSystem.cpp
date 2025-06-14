#include "ParticleSystem.h"


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

namespace Trengine {
	ParticleSystem::ParticleSystem()
	{
		particlePool.resize(1000);
	}

	void ParticleSystem::emit(const ParticleProps& particleProps)
	{
		Particle& particle = particlePool[poolIndex];
		particle.active = true;
		particle.position = particleProps.position;
		particle.rotation = Random::Float() * 2.0f * glm::pi<float>();

		// Velocity
		particle.velocity = particleProps.velocity;
		particle.velocity.x += particleProps.velocityVariation.x * (Random::Float() - 0.5f);
		particle.velocity.y += particleProps.velocityVariation.y * (Random::Float() - 0.5f);

		// Color
		particle.colorBegin = particleProps.colorBegin;
		particle.colorEnd = particleProps.colorEnd;

		// Size
		particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (Random::Float() - 0.5f);
		particle.sizeEnd = particleProps.sizeEnd;

		// Life
		particle.lifeTime = particleProps.lifeTime;
		particle.lifeRemaining = particleProps.lifeTime;

		poolIndex = --poolIndex % particlePool.size();
	}

	void ParticleSystem::onUpdate(Timestep ts)
	{
		for (auto& particle : particlePool)
		{
			if (!particle.active)
				continue;

			if (particle.lifeRemaining <= 0.0f)
			{
				particle.active = false;
				continue;
			}

			particle.lifeRemaining -= ts;
			particle.position += particle.velocity * (float)ts;
			particle.rotation += 0.01f * ts;
		}
	}

	void ParticleSystem::onRender()
	{
		for (auto& particle : particlePool)
		{
			if (!particle.active)
				continue;

			float life = particle.lifeRemaining / particle.lifeTime;
			glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);
			color.a = color.a * life;

			float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);
			//particle.Position, { size, size }, particle.Rotation
			Renderer2D::drawQuad(particle.position, { size, size }, particle.rotation, color);
		}
	}
}