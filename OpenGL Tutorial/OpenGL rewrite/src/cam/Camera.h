#pragma once
#include <../Dependencies/glm/glm.hpp>

class Camera
{
	glm::vec3 m_position;
	glm::vec3 m_viewDirection;
	const glm::vec3 m_UP;
	glm::vec2 m_oldMousePosition;
	glm::vec3 m_strafeDirection;
	static const float MOVEMENT_SPEED;

public:
	Camera();
	void mouseUpdate(const glm::vec2& newMousePosition);
	glm::mat4 GetWorldToViewMatrix() const;

public: //move functions

	void MoveForward();
	void MoveBackward();
	void StrafeLeft();
	void StrafeRight();
	void MoveUp();
	void MoveDown();

};

