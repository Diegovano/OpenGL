#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include "../logger.h"

const float Camera::MOVEMENT_SPEED = 0.02f;

Camera::Camera() : m_viewDirection(-0.0672515184f, -0.636077762f, -0.768687665f),
	m_UP(0.0f,1.0f,0.0f), m_position(0.201957405f, 3.63646984f, 4.53021145f)
{
}

void Camera::MouseUpdate(const glm::vec2& newMousePosition)
{
	const float ROTATION_SPEED = 0.5f;

	glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;

	m_strafeDirection = glm::cross(m_viewDirection, m_UP);

	glm::mat4 rotator = glm::rotate(-glm::radians(mouseDelta.x)*ROTATION_SPEED, m_UP) *
						glm::rotate(-glm::radians(mouseDelta.y)*ROTATION_SPEED, m_strafeDirection);

	m_viewDirection = glm::mat3(rotator) * m_viewDirection;
	m_oldMousePosition = newMousePosition;
}

glm::mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_viewDirection, m_UP);
}


void Camera::MoveForward()
{
	m_position += MOVEMENT_SPEED * m_viewDirection;
}
void Camera::MoveBackward()
{
	m_position += -MOVEMENT_SPEED * m_viewDirection;
}

void Camera::StrafeLeft()
{
	m_position += -MOVEMENT_SPEED * m_strafeDirection;
}

void Camera::StrafeRight()
{
	m_position += MOVEMENT_SPEED * m_strafeDirection;
}

void Camera::MoveUp()
{
	m_position += MOVEMENT_SPEED * m_UP;
}

void Camera::MoveDown()
{
	m_position += -MOVEMENT_SPEED * m_UP;
}