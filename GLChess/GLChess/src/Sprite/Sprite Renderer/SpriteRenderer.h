#pragma once
#include "../../Abstraction/GLabs.h"
#include "../../Abstraction/2DTexture/2DTexture.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SpriteRenderer
{
	GLabs::ShaderProgram shaderProgram;
	GLabs::VertexArray quadVAO;

	void InitRenderData();

public:
	SpriteRenderer(GLabs::ShaderProgram p_shaderProgram) : shaderProgram(p_shaderProgram)
	{
		InitRenderData();
	}
//	~SpriteRenderer();

	void DrawSprite(GLabs::Texture p_texture, glm::vec2 p_position,
		glm::vec2 p_size = glm::vec2(0.2f, 0.2f), GLfloat p_rotate = 180.0f,
		glm::vec3 p_colour = glm::vec3(1.0f));
};

