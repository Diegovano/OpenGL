#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

enum movement_t
{
	RIGHT,

	LEFT,

	UP,

	DOWN
};

class Entity
{
public:
	Entity(const glm::vec2& position, const glm::vec3& color)
		: m_position(position), m_color(color)
	{
	}

	void Move(movement_t movetype, float time)
	{
		static constexpr float SPEED = 1.0f;
		switch (movetype)
		{
		case RIGHT: m_position.x += time * SPEED;
		case LEFT:  m_position.x -= time * SPEED;
		case UP:	m_position.y += time * SPEED;
		case DOWN:  m_position.y -= time * SPEED;
		}
	}

	const glm::vec2& Position(void) const
	{
		return m_position;
	}
	const glm::vec3& Color(void) const
	{
		return m_color;
	}
private:
	glm::vec2 m_position;
	glm::vec3 m_color;
};