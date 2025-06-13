#include "Level.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Trengine;

static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
	int H = (int)(hsv.x * 360.0f);
	double S = hsv.y;
	double V = hsv.z;

	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
}

static bool PointInTri(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
{
	float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}


void Level::init()
{
	triangleTexture = Texture2D::create("assets/textures/Triangle.png");
	player.loadAssets();

	pillars.resize(5);
	for (int i = 0; i < 5; i++)
		createPillar(i, i * 10.0f);
}

void Level::onUpdate(Timestep ts)
{
	player.onUpdate(ts);

	if (collisionTest())
	{
		gameOverFunc();
		return;
	}

	pillarHSV.x += 0.1f * ts;
	if (pillarHSV.x > 1.0f)
		pillarHSV.x = 0.0f;

	if (player.getPosition().x > pillarTarget)
	{
		createPillar(pillarIndex, pillarTarget + 20.0f);
		pillarIndex = ++pillarIndex % pillars.size();
		pillarTarget += 10.0f;
	}
}

void Level::onRender()
{
	const auto& playerPos = player.getPosition();

	glm::vec4 color = HSVtoRGB(pillarHSV);

	// Background
	Renderer2D::drawQuad(glm::translate(glm::mat4(1) ,{ playerPos.x, 0.0f, -0.8f }) * glm::scale(glm::mat4(1),{ 50.0f, 50.0f, 1 }), { 0.3f, 0.3f, 0.3f, 1.0f });

	// Floor and ceiling
	Renderer2D::drawQuad(glm::translate(glm::mat4(1), { playerPos.x,  34.0f, 0 })* glm::scale(glm::mat4(1), { 50.0f, 50.0f,1 }), color);
	Renderer2D::drawQuad(glm::translate(glm::mat4(1), {  playerPos.x, -34.0f,0 })* glm::scale(glm::mat4(1),{50.0f, 50.0f,1}), color);

	for (auto& pillar : pillars)
	{
		Renderer2D::drawQuad(glm::translate(glm::mat4(1), pillar.TopPosition)*glm::rotate(glm::mat4(1), glm::radians(180.0f), {0,0,1}) * glm::scale(glm::mat4(1), {pillar.TopScale,1}), triangleTexture, color);
		Renderer2D::drawQuad(glm::translate(glm::mat4(1), pillar.BottomPosition) * glm::scale(glm::mat4(1), { pillar.BottomScale,1 }), triangleTexture, color);
	}

	player.onRender();
}

void Level::onImGuiRender()
{
	player.onImGuiRender();
}

void Level::createPillar(int index, float offset)
{
	Pillar& pillar = pillars[index];
	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;
	pillar.TopPosition.z = index * 0.1f - 0.5f;
	pillar.BottomPosition.z = index * 0.1f - 0.5f + 0.05f;

	float center = Random::Float() * 35.0f - 17.5f;
	float gap = 2.0f + Random::Float() * 5.0f;

	pillar.TopPosition.y = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
	pillar.BottomPosition.y = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
}

bool Level::collisionTest()
{
	if (glm::abs(player.getPosition().y) > 8.5f)
		return true;

	glm::vec4 playerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};

	const auto& pos = player.getPosition();
	glm::vec4 playerTransformedVerts[4];
	for (int i = 0; i < 4; i++)
	{
		playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f })
			* glm::rotate(glm::mat4(1.0f), glm::radians(player.getRotation()), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { 1.0f, 1.3f, 1.0f })
			* playerVertices[i];
	}


	// To match Triangle.png (each corner is 10% from the texture edge)
	glm::vec4 pillarVertices[3] = {
		{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
	};

	for (auto& p : pillars)
	{
		glm::vec2 tri[3];

		// Top pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), { p.TopPosition.x, p.TopPosition.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { p.TopScale.x, p.TopScale.y, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

		// Bottom pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), { p.BottomPosition.x, p.BottomPosition.y, 0.0f })
				* glm::scale(glm::mat4(1.0f), { p.BottomScale.x, p.BottomScale.y, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

	}
	return false;
}

void Level::gameOverFunc()
{
	gameOver = true;
}

void Level::reset()
{
	gameOver = false;

	player.reset();

	pillarTarget = 30.0f;
	pillarIndex = 0;
	for (int i = 0; i < 5; i++)
		createPillar(i, i * 10.0f);
}