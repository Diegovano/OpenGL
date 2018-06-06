#include <iostream>
#include <fstream>
#include "Window/Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "abs/GLabs.h"
#include "geo/Vertex.h"
#include "geo/ShapeGenerator.h"
#include "cam/Camera.h"

const unsigned int NUM_VERTS_TRI = 3;
const unsigned int NUM_FLOATS_VERTS = 6;
const unsigned int VERTEX_BYTE_SIZE = NUM_FLOATS_VERTS * sizeof(float);
GLuint numIndices;
Camera camera;

void sendDataToOpenGL() 
{
	ShapeData shape = ShapeGenerator::MakeCube();
	GLabs::Buffer vertexBuffer;
	vertexBuffer.Data(GL_ARRAY_BUFFER, shape.VertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	GLabs::Buffer elementBuffer;
	elementBuffer.Data(GL_ELEMENT_ARRAY_BUFFER, shape.IndexBufferSize(), shape.indices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	numIndices = shape.numIndices;

	shape.CleanUp();

	GLabs::Buffer tranformationMatrixBuffer;
	tranformationMatrixBuffer.Bind(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 2, 0, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0 * sizeof(float)));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(4 * sizeof(float)));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(8 * sizeof(float)));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(12 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);  
}

GLuint ShaderProgram()
{
	std::ifstream vshFileStream("D:\\Program Files (x86)\\msdev\\OpenGL\\OpenGL Tutorial\\OpenGL rewrite\\rsc\\sh\\vsh.shader");
	std::ifstream fshFileStream("D:\\Program Files (x86)\\msdev\\OpenGL\\OpenGL Tutorial\\OpenGL rewrite\\rsc\\sh\\fsh.shader");

	std::string StrVertex = std::string(std::istreambuf_iterator<char>(vshFileStream), std::istreambuf_iterator<char>());
	std::string StrFragment = std::string(std::istreambuf_iterator<char>(fshFileStream), std::istreambuf_iterator<char>());
	
	const char* vshCStr[1] = { StrVertex.c_str() };
	const char* fshCStr[1] = { StrFragment.c_str() };

	GLabs::Shader VertexShader(GL_VERTEX_SHADER), FragmentShader(GL_FRAGMENT_SHADER);

	VertexShader.AttachSource(vshCStr);
	FragmentShader.AttachSource(fshCStr);

	VertexShader.Compile();
	FragmentShader.Compile();

	GLabs::ShaderProgram Program;

	Program.AttachShader(VertexShader);
	Program.AttachShader(FragmentShader);

	Program.Link();

	Program.UseProgram();

	FragmentShader.Delete();
	VertexShader.Delete();

	return Program.ProgramID();
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	int halfWidth, halfHeight;
	glfwGetWindowSize(window, &halfWidth, &halfHeight);
	halfWidth /= 2;
	halfHeight /= 2;

	camera.mouseUpdate(glm::vec2((xpos - halfWidth), (ypos - halfHeight)));
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case(GLFW_KEY_W):
		camera.MoveForward();
		break;
	case(GLFW_KEY_A):
		camera.StrafeLeft();
		break;
	case(GLFW_KEY_S):
		camera.MoveBackward();
		break;
	case(GLFW_KEY_D):
		camera.StrafeRight();
		break;
	case(GLFW_KEY_R):
		camera.MoveUp();
		break;
	case(GLFW_KEY_F):
		camera.MoveDown();
		break;
	}
}

int main(int argc, char* argv[])
{
	Window window("Superb Window", 1280, 720);
	window.WindowInit();
	window.SetIcon("rsc\\icon.png", 64);
	window.OpenGLInit();

	sendDataToOpenGL();
	GLuint programID = ShaderProgram();

	window.SetCursorPosCallback(cursor_position_callback);
	window.SetKeyCallback(key_callback);

	while (window.WindowOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(+0.0f, +0.0f, +0.0f, +1.0f);

		int currWidth, currHeight;
		window.WindowGetSize(currWidth, currHeight);
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(75.0f), (float)currWidth / (float)currHeight, 0.1f, 10.0f);
		glm::mat4 fullTransforms[] =
		{
			projectionMatrix * camera.GetWorldToViewMatrix() * glm::translate(glm::vec3(-1.0f, 0.0f, -3.0f)) * glm::rotate(glm::radians(36.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
			projectionMatrix * camera.GetWorldToViewMatrix() * glm::translate(glm::vec3(1.0f, 0.0f, -3.75f)) * glm::rotate(glm::radians(126.0f), glm::vec3(0.0f, 1.0f, 0.0f))
		}; 
		glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);

		glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);

//		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

		window.WindowUpdate();
	}

	glUseProgram(0);
	glDeleteProgram(programID);
	window.WindowDestroy();
	glfwTerminate();
	return 0;
}