#include "Player.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Trengine/Core/Input.h"
#include "Trengine/Core/KeyCodes.h"

using namespace Trengine;

Player::Player()
{
	// Smoke
	smokeParticle.Position = { 0.0f, 0.0f };
	smokeParticle.Velocity = { -2.0f, 0.0f }, smokeParticle.VelocityVariation = { 4.0f, 2.0f };
	smokeParticle.SizeBegin = 0.35f, smokeParticle.SizeEnd = 0.0f, smokeParticle.SizeVariation = 0.15f;
	smokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	smokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	smokeParticle.LifeTime = 4.0f;

	// Flames
	engineParticle.Position = { 0.0f, 0.0f };
	engineParticle.Velocity = { -2.0f, 0.0f }, engineParticle.VelocityVariation = { 3.0f, 1.0f };
	engineParticle.SizeBegin = 0.5f, engineParticle.SizeEnd = 0.0f, engineParticle.SizeVariation = 0.3f;
	engineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	engineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
	engineParticle.LifeTime = 1.0f;
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
		engineParticle.Position = position + glm::vec2{ rotated.x, rotated.y };
		engineParticle.Velocity.y = -velocity.y * 0.2f - 0.2f;
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
		smokeParticle.Position = position;
		particleSystem.emit(smokeParticle);
		smokeNextEmitTime += smokeEmitInterval;
	}

	particleSystem.onUpdate(ts);
}

void Player::onRender()
{
	particleSystem.onRender();
	Renderer2D::drawQuad(glm::translate(glm::mat4(1), { position.x, position.y, 0.5f })*glm::rotate(glm::mat4(1), glm::radians(getRotation()), {0,0,1}) * glm::scale(glm::mat4(1), {1.0f, 1.3f,1}), shipTexture);
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
