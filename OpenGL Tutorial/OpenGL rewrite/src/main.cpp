#include <iostream>
#include <fstream>
#include "Window/Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "abs/GLabs.h"
#include "geo/Vertex.h"
#include "geo/ShapeGenerator.h"

const unsigned int NUM_VERTS_TRI = 3;
const unsigned int NUM_FLOATS_VERTS = 6;
const unsigned int VERTEX_BYTE_SIZE = NUM_FLOATS_VERTS * sizeof(float);
GLuint cubeNumIndices;
GLuint arrowNumIndices;
Camera camera;
GLuint fullTransformationUniformLocation;
GLabs::VertexArray* cubeVertexArrayObject, *arrowVertexArrayObject;
GLabs::Buffer* vertexBuffer, *elementBuffer, *vertexBuffer2, *elementBuffer2;

void SendDataToOpenGL() 
{
	ShapeData shape = ShapeGenerator::MakeCube();
	vertexBuffer = new GLabs::Buffer;
	elementBuffer = new GLabs::Buffer;

	vertexBuffer->Data(GL_ARRAY_BUFFER, shape.VertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	elementBuffer->Data(GL_ELEMENT_ARRAY_BUFFER, shape.IndexBufferSize(), shape.indices, GL_STATIC_DRAW);
	
	cubeNumIndices = shape.numIndices;

	shape.CleanUp();	
	
	shape = ShapeGenerator::MakeArrow();
	vertexBuffer2 = new GLabs::Buffer;
	elementBuffer2 = new GLabs::Buffer;

	vertexBuffer2->Data(GL_ARRAY_BUFFER, shape.VertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	elementBuffer2->Data(GL_ELEMENT_ARRAY_BUFFER, shape.IndexBufferSize(), shape.indices, GL_STATIC_DRAW);

	arrowNumIndices = shape.numIndices;

	shape.CleanUp();

}

void SetupVertexArrays()
{
	cubeVertexArrayObject = new GLabs::VertexArray;
	arrowVertexArrayObject = new GLabs::VertexArray;

	cubeVertexArrayObject->Bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	vertexBuffer->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	elementBuffer->Bind(GL_ELEMENT_ARRAY_BUFFER);

	arrowVertexArrayObject->Bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	vertexBuffer2->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	elementBuffer2->Bind(GL_ELEMENT_ARRAY_BUFFER);
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

static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	int halfWidth, halfHeight;
	glfwGetWindowSize(window, &halfWidth, &halfHeight);
	halfWidth /= 2;
	halfHeight /= 2;

	camera.MouseUpdate(glm::vec2((xpos - halfWidth), (ypos - halfHeight)));
}

int main(int argc, char* argv[])
{
	Window window("Luc, why are you looking here?", 1280, 720, &camera);
	window.WindowSetIcon("rsc\\icon.png", 64);

	window.SetCursorPosCallback(CursorPositionCallback);

	GLuint programID = ShaderProgram();

	fullTransformationUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");


	while (window.WindowOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(+0.0f, +0.0f, +0.0f, +1.0f);

		glm::mat4 fullTransformMatrix;
		glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(60.0f), window.WindowAspectRatio(), 0.01f, 10.0f);
		glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
		glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

		// Cube
		cubeVertexArrayObject->Bind();

		glm::mat4 cube1ModelToWorldMatrix =
			glm::translate(glm::vec3(-2.0f, 0.0f, -3.0f)) *
			glm::rotate(glm::radians(36.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;
		glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

		glm::mat4 cube2ModelToWorldMatrix =
			glm::translate(glm::vec3(2.0f, 0.0f, -3.75f)) *
			glm::rotate(glm::radians(127.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		fullTransformMatrix = worldToProjectionMatrix * cube2ModelToWorldMatrix;
		glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);  

		// Arrow
		arrowVertexArrayObject->Bind();

		glm::mat4 arrowModelToWorldMatrix = glm::translate(glm::vec3(0.0f, 0.0f, -3.0f));
		fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;
		glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, 0);

		GLabs::VertexArray::Unbind();

		window.WindowUpdate();
	}

	glUseProgram(0);
	glDeleteProgram(programID);
	delete vertexBuffer, vertexBuffer2, elementBuffer, elementBuffer2;
	window.WindowDestroy();
	glfwTerminate();
	return 0;
}