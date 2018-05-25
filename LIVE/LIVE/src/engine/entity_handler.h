#pragma once

#include <array>
#include "entity.h"
#include "buffer.h"

class EntityHandler
{
public:
	EntityHandler(void)
		: m_entities{ Entity{ glm::vec2(-0.5f, +0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
					  Entity{ glm::vec2(+0.5f, +0.0f), glm::vec3(0.0f, 1.0f, 0.0f) } }
	{
	}
	void ModelInit(void)
	{
		VertInit();
		IndicesInit();
		VAInit();
	}
private:
	void VertInit(void)
	{
		glm::vec2 verts[]
		{
			glm::vec2(-0.1f, -0.1f),
			glm::vec2(-0.1f, +0.1f),
			glm::vec2(+0.1f, +0.1f),
			glm::vec2(+0.1f, -0.1f)
		};
		m_vertBuffer.Init(sizeof(verts), verts, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
	}
	void IndicesInit(void)
	{
		uint16_t indices[]
		{
			0, 1, 2,
			0, 1, 3
		};
		m_indexBuffer.Init(sizeof(indices), indices, GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);
	}
	void VAInit(void)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), nullptr);
	}
private:
	// the players
	std::array<Entity, 2> m_entities;
	Buffer m_vertBuffer;
	Buffer m_indexBuffer;
};