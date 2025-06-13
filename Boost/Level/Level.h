#pragma once

#include "../Player/Player.h"

namespace Trengine {
	struct Pillar
	{
		glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };
		glm::vec2 TopScale = { 15.0f, 20.0f };

		glm::vec3 BottomPosition = { 10.0f, 10.0f, 0.0f };
		glm::vec2 BottomScale = { 15.0f, 20.0f };
	};

	class Level
	{
	public:
		void init();

		void onUpdate(Timestep ts);
		void onRender();

		void onImGuiRender();

		bool isGameOver() const { return gameOver; }
		void reset();

		Player& getPlayer() { return player; }
	private:
		void createPillar(int index, float offset);
		bool collisionTest();

		void gameOverFunc();
	private:
		Player player;

		bool gameOver = false;

		float pillarTarget = 30.0f;
		int pillarIndex = 0;
		glm::vec3 pillarHSV = { 0.0f, 0.8f, 0.8f };

		std::vector<Pillar> pillars;

		std::shared_ptr<Texture2D> triangleTexture;
	};
}