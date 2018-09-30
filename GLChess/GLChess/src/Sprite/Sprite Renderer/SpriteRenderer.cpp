#include "SpriteRenderer.h"

void SpriteRenderer::InitRenderData()
{
	GLabs::Buffer vertexBuffer;

	GLfloat vertices[]
	{
		0.0f, 1.0f,
		0.0f, 1.0f,

		1.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		0.0f, 1.0f,
		
		1.0f, 1.0f,
		1.0f, 1.0f,

		1.0f, 0.0f,
		1.0f, 0.0f
	};

	vertexBuffer.Data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	quadVAO.Bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	quadVAO.Unbind();

	vertexBuffer.Unbind();
}

void SpriteRenderer::DrawSprite(GLabs::Texture p_texture, glm::vec2 p_position,
	glm::vec2 p_size, GLfloat p_rotate,
	glm::vec3 p_colour)
{
	shaderProgram.UseProgram();
	glm::mat4 fullTransformMatrix(1);

	fullTransformMatrix = glm::translate(fullTransformMatrix, glm::vec3(p_position, 0.0f));
	fullTransformMatrix = glm::rotate(fullTransformMatrix, glm::radians(p_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	fullTransformMatrix = glm::translate(fullTransformMatrix, glm::vec3(-0.5f * p_size.x, -0.5f * p_size.y, 0.0f));
	fullTransformMatrix = glm::scale(fullTransformMatrix, glm::vec3(p_size, 1.0f));

	GLuint fullTransformMatrixUniformLocation = glGetUniformLocation(shaderProgram.ProgramID(), "full_transform_matrix");
	GLuint spriteColourUniformLocation = glGetUniformLocation(shaderProgram.ProgramID(), "sprite_colour");

	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glUniform3fv(spriteColourUniformLocation, 1, &p_colour[0]);

	glActiveTexture(GL_TEXTURE0);
	p_texture.Bind();

	quadVAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	quadVAO.Unbind();
}