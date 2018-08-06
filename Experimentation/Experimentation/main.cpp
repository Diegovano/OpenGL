#include "Window/Window.h"
#include "sh/ShaderProgram.h"
#include "Render Manager/Render Manager.h"
#include "Vertex.h"

int main(int argc, char* argv[])
{
	Window window("Experimentation", 1280, 720);

	GLabs::Buffer triangleBuffer;

	Vertex vertices[]
	{
		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),

		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	GLushort indices[]
	{
		0, 1, 2
	};

	triangleBuffer.Reserve(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices) + sizeof(indices), GL_STATIC_DRAW);

	triangleBuffer.SubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	triangleBuffer.SubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), sizeof(indices), indices);

	RenderManager render;

	GLuint programID = ShaderProgram();
	while (window.WindowOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleBuffer.BufferID());
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)sizeof(vertices));

//		render.AddBuffer(BufferData(triangleBuffer.BufferID(), 3));

//		render.DrawAllBuffers();

		window.WindowUpdate();
	}
	window.WindowDestroy();
	return 0;
}