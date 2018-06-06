#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include "../logger.h"

Camera::Camera() : m_viewDirection(0.0f, 0.0f, -1.0f),
	m_UP(0.0f,1.0f,0.0f), m_position(0.0f,0.0f,0.0f)
{
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	const float ROTATION_SPEED = 0.1f;

	glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;
	m_viewDirection = glm::mat3(glm::rotate(-glm::radians(mouseDelta.x) * ROTATION_SPEED, m_UP)) * m_viewDirection;
//	Log(-glm::radians(mouseDelta.x) * ROTATION_SPEED);
//	Log(mouseDelta.x);
	
	glm::vec3 toRotate = glm::cross(m_viewDirection, m_UP);
	m_viewDirection = glm::mat3(glm::rotate(-glm::radians(mouseDelta.y) * ROTATION_SPEED, toRotate)) * m_viewDirection;
//	Log(-glm::radians(mouseDelta.y) * ROTATION_SPEED);
//	Log(mouseDelta.y);

	m_oldMousePosition = newMousePosition;
}

glm::mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_viewDirection, m_UP);
}
