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
GLuint teapotNumIndices;
GLuint arrowNumIndices;
GLuint planeNumIndices;
Camera camera;
GLuint fullTransformationUniformLocation;
GLuint arrowIndexDataByteOffset;
GLuint teapotIndexDataByteOffset;
GLuint planeIndexDataByteOffset;

GLabs::VertexArray* teapotVertexArrayObject, *arrowVertexArrayObject, *planeVertexArrayObject;
GLabs::Buffer* Buffer;


void SendDataToOpenGL() 
{
	ShapeData teapot = ShapeGenerator::MakeTeapot(10);
	ShapeData arrow = ShapeGenerator::MakeArrow();
	ShapeData plane = ShapeGenerator::MakePlane(20);

	Buffer = new GLabs::Buffer;

	Buffer->Reserve(GL_ARRAY_BUFFER, teapot.VertexBufferSize() + teapot.IndexBufferSize() +
		arrow.VertexBufferSize() + arrow.IndexBufferSize() + plane.VertexBufferSize() + plane.IndexBufferSize() , GL_STATIC_DRAW);

	GLsizeiptr currentOffset = 0; 
	Buffer->SubData(GL_ARRAY_BUFFER, currentOffset, teapot.VertexBufferSize(), teapot.vertices);
	currentOffset += teapot.VertexBufferSize();
	Buffer->SubData(GL_ARRAY_BUFFER, currentOffset, teapot.IndexBufferSize(), teapot.indices);
	currentOffset += teapot.IndexBufferSize();
	Buffer->SubData(GL_ARRAY_BUFFER, currentOffset, arrow.VertexBufferSize(), arrow.vertices);
	currentOffset += arrow.VertexBufferSize();
	Buffer->SubData(GL_ARRAY_BUFFER, currentOffset, arrow.IndexBufferSize(), arrow.indices);
	currentOffset += arrow.IndexBufferSize();
	Buffer->SubData(GL_ARRAY_BUFFER, currentOffset, plane.VertexBufferSize(), plane.vertices);
	currentOffset += plane.VertexBufferSize();
	Buffer->SubData(GL_ARRAY_BUFFER, currentOffset, plane.IndexBufferSize(), plane.indices);

	teapotNumIndices = teapot.numIndices;
	arrowNumIndices = arrow.numIndices;
	planeNumIndices = plane.numIndices;

	teapotVertexArrayObject = new GLabs::VertexArray;
	arrowVertexArrayObject = new GLabs::VertexArray;
	planeVertexArrayObject = new GLabs::VertexArray;

	teapotVertexArrayObject->Bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Buffer->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	Buffer->Bind(GL_ELEMENT_ARRAY_BUFFER);

	arrowVertexArrayObject->Bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLuint arrowByteOffset = teapot.VertexBufferSize() + teapot.IndexBufferSize();
	Buffer->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)arrowByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(arrowByteOffset + 3 * sizeof(float)));
	Buffer->Bind(GL_ELEMENT_ARRAY_BUFFER);

	planeVertexArrayObject->Bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLuint planeByteOffset = arrowByteOffset + arrow.VertexBufferSize() + arrow.IndexBufferSize(); //had forgotten to add arrowOffset and plane.Vetex() and plane.Index()
	Buffer->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)planeByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(planeByteOffset + 3 * sizeof(float)));
	Buffer->Bind(GL_ELEMENT_ARRAY_BUFFER);

	teapotIndexDataByteOffset = teapot.VertexBufferSize();
	arrowIndexDataByteOffset = arrowByteOffset + arrow.VertexBufferSize(); //had written - arrow.IndexBufferSize()
	planeIndexDataByteOffset = planeByteOffset + plane.VertexBufferSize();

	teapot.CleanUp();	
	arrow.CleanUp();
	plane.CleanUp();
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
		glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(60.0f), window.WindowAspectRatio(), 0.1f, 50.0f);
		glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
		glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

		// Teapot
		teapotVertexArrayObject->Bind();

		glm::mat4 teapot1ModelToWorldMatrix =
			glm::translate(glm::vec3(-3.0f, 0.0f, -6.0f)) *
			glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		fullTransformMatrix = worldToProjectionMatrix * teapot1ModelToWorldMatrix;
		glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, teapotNumIndices, GL_UNSIGNED_SHORT, (void*)teapotIndexDataByteOffset);

		glm::mat4 teapot2ModelToWorldMatrix =
			glm::translate(glm::vec3(3.0f, 0.0f, -6.75f)) *
			glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		fullTransformMatrix = worldToProjectionMatrix * teapot2ModelToWorldMatrix;
		glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, teapotNumIndices, GL_UNSIGNED_SHORT, (void*)teapotIndexDataByteOffset);

		// Arrow
		arrowVertexArrayObject->Bind();

		glm::mat4 arrowModelToWorldMatrix = glm::translate(glm::vec3(0.0f, 0.0f, -3.0f));
		fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;
		glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexDataByteOffset);

		// Plane
		planeVertexArrayObject->Bind();

		glm::mat4 planeModelToWorldMatrix = glm::mat4(1);
		fullTransformMatrix = worldToProjectionMatrix * planeModelToWorldMatrix;
		glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, planeNumIndices, GL_UNSIGNED_SHORT, (void*)planeIndexDataByteOffset);

		GLabs::VertexArray::Unbind();

		window.WindowUpdate();
	}

	glUseProgram(0);
	glDeleteProgram(programID);
	Buffer->DeleteBuffer();
	delete Buffer;
	window.WindowDestroy();
	glfwTerminate();
	return 0;
}