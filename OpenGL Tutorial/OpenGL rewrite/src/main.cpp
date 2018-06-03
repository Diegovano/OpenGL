#include <iostream>
#include <fstream>
#include <vector>
#include "../Dependencies/GLEW/include/GL/glew.h"
#include "../Dependencies/GLFW/include/GLFW/glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "abs/GLabs.h"
#include "geo/Vertex.h"
#include "geo/ShapeGenerator.h"

const unsigned int NUM_VERTS_TRI = 3;
const unsigned int NUM_FLOATS_VERTS = 6;
const unsigned int VERTEX_BYTE_SIZE = NUM_FLOATS_VERTS * sizeof(float);
GLuint numIndices;

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

	Program.AddAttribute(0, "vertex_position");
	Program.AddAttribute(1, "vertex_colour");

	Program.Link();
	Program.UseProgram();

	return Program.ProgramID();
}

int main()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW Initialisation failure!" << std::endl;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 720, "Superb Window", 0, 0);
	glfwMakeContextCurrent(window);

	GLenum errCode = glewInit();
	if (errCode != GLEW_OK)
	{
		std::cerr << "GLEW Intialisation failure!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	sendDataToOpenGL();
	GLuint program = ShaderProgram();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(+0.0f, +0.0f, +0.0f, +1.0f);
		int height, width;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), (float)width/(float)height, 0.1f, 10.0f);
		glm::mat4 projectionTranslationMatrix = glm::translate(projectionMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 fullTransformMatrix = glm::rotate(projectionTranslationMatrix, glm::radians(56.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		GLint fullTransformMatrixUniformLocation =
			glGetUniformLocation(program, "fullTransformMatrix");

		glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1,
			GL_FALSE, &fullTransformMatrix[0][0]);

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}