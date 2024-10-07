#include "trpch.h"
#include "Camera.h"

Trengine::SceneCamera::SceneCamera(const glm::mat4& proj)
	: Camera(proj)
{
	recalculateProjection();
}

void Trengine::SceneCamera::setOrthographic(float size, float nearClip, float farClip)
{
	orthographicSize = size;
	orthographicNear = nearClip;
	orthographicFar = farClip;

	recalculateProjection();
}

void Trengine::SceneCamera::setViewportSize(uint32_t width, uint32_t height)
{
	aspectRatio = (float)width / (float)height;
	recalculateProjection();
}

void Trengine::SceneCamera::recalculateProjection()
{
	float orthoLeft = -orthographicSize * aspectRatio * 0.5f;
	float orthoRight = orthographicSize * aspectRatio * 0.5f;
	float orthoBottom = -orthographicSize * 0.5f;
	float orthoTop = orthographicSize * 0.5f;

	projection = glm::ortho(orthoLeft, orthoRight,
		orthoBottom, orthoTop, orthographicNear, orthographicFar);
}


