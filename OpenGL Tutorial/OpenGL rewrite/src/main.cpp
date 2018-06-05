#include <iostream>
#include <fstream>
#include <vector>
#include <GLEW/include/GL/glew.h>
#include <GLFW/include/GLFW/glfw3.h>
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

//	Program.AddAttribute(0, "vertex_position");
//	Program.AddAttribute(1, "vertex_colour");

	Program.Link();

	GLint positionLocation = glGetAttribLocation(Program.ProgramID(), "position");

	Program.UseProgram();

	FragmentShader.Delete();
	VertexShader.Delete();

	return Program.ProgramID();
}

int main()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW Initialisation failure!" << std::endl;
	}

	double aspectRatio = 16 / 9;
	int width = 1920, height = (width / 16) * 9; //Window dimentions

	GLFWwindow* window;
	window = glfwCreateWindow(width, height, "Superb Window", 0, 0);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	GLenum errCode = glewInit();
	if (errCode != GLEW_OK)
	{
		std::cerr << "GLEW Intialisation failure!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	sendDataToOpenGL();
	GLuint programID = ShaderProgram();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(+0.0f, +0.0f, +0.0f, +1.0f);

		int tempHeight, tempWidth;
		glfwGetWindowSize(window, &tempWidth, &tempHeight);
		glViewport(0, 0, tempWidth, tempHeight);

		const int SENSITIVITYDIV = 20;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		camera.mouseUpdate(glm::vec2((xpos - tempWidth/2)/SENSITIVITYDIV, (ypos - tempHeight/2)/SENSITIVITYDIV));

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(75.0f), (float)width / (float)height, 0.1f, 10.0f);
		glm::mat4 fullTransforms[] =
		{
			projectionMatrix * camera.GetWorldToViewMatrix() * glm::translate(glm::vec3(-1.0f, 0.0f, -3.0f)) * glm::rotate(glm::radians(36.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
			projectionMatrix * camera.GetWorldToViewMatrix() * glm::translate(glm::vec3(1.0f, 0.0f, -3.75f)) * glm::rotate(glm::radians(126.0f), glm::vec3(0.0f, 1.0f, 0.0f))
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);

		glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glUseProgram(0);
	glDeleteProgram(programID);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}