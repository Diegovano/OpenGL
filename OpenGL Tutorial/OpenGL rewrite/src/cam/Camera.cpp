#include "Camera.h"
#include <glm/gtx/transform.hpp>

Camera::Camera() : m_viewDirection(0.0f, 0.0f, -1.0f),
	m_UP(0.0f,1.0f,0.0f), m_position(0.0f,0.0f,0.0f)
{
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - m_oldMousePosition;
	m_viewDirection = glm::mat3(glm::rotate(glm::radians(-mouseDelta.x), m_UP)) * m_viewDirection;
	m_oldMousePosition = newMousePosition;
}

glm::mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_viewDirection, m_UP);
}
