#include "Player.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Trengine/Core/Input.h"
#include "Trengine/Core/KeyCodes.h"

using namespace Trengine;

Player::Player()
{
	// Smoke
	smokeParticle.position = { 0.0f, 0.0f };
	smokeParticle.velocity = { -2.0f, 0.0f }, smokeParticle.velocityVariation = { 4.0f, 2.0f };
	smokeParticle.sizeBegin = 0.35f, smokeParticle.sizeEnd = 0.0f, smokeParticle.sizeVariation = 0.15f;
	smokeParticle.colorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	smokeParticle.colorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	smokeParticle.lifeTime = 4.0f;

	// Flames
	engineParticle.position = { 0.0f, 0.0f };
	engineParticle.velocity = { -2.0f, 0.0f }, engineParticle.velocityVariation = { 3.0f, 1.0f };
	engineParticle.sizeBegin = 0.5f, engineParticle.sizeEnd = 0.0f, engineParticle.sizeVariation = 0.3f;
	engineParticle.colorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	engineParticle.colorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
	engineParticle.lifeTime = 1.0f;
}

void Player::loadAssets()
{
	shipTexture = Texture2D::create("assets/textures/Ship.png");
}

void Player::onUpdate(Timestep ts)
{
	time += ts;

	if (Input::isKeyPressed(TR_KEY_SPACE))
	{
		velocity.y += enginePower;
		if (velocity.y < 0.0f)
			velocity.y += enginePower * 2.0f;

		// Flames
		glm::vec2 emissionPoint = { 0.0f, -0.6f };
		float rotation = glm::radians(getRotation());
		glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);
		engineParticle.position = position + glm::vec2{ rotated.x, rotated.y };
		engineParticle.velocity.y = -velocity.y * 0.2f - 0.2f;
		particleSystem.emit(engineParticle);
	}
	else
	{
		velocity.y -= gravity;
	}

	velocity.y = glm::clamp(velocity.y, -20.0f, 20.0f);
	position += velocity * (float)ts;

	// Particles
	if (time > smokeNextEmitTime)
	{
		smokeParticle.position = position;
		particleSystem.emit(smokeParticle);
		smokeNextEmitTime += smokeEmitInterval;
	}

	particleSystem.onUpdate(ts);
}

void Player::onRender()
{
	particleSystem.onRender();
	Renderer2D::drawQuad({ position.x, position.y, 0.5f }, { 1.0f, 1.3f }, glm::radians(getRotation()), shipTexture);
}

void Player::onImGuiRender()
{
	ImGui::DragFloat("Engine Power", &enginePower, 0.1f);
	ImGui::DragFloat("Gravity", &gravity, 0.1f);
}

void Player::reset()
{
	position = { -10.0f, 0.0f };
	velocity = { 5.0f, 0.0f };
}
