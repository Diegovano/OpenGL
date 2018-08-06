#pragma once
#include <GL/glew.h>
#include "Vertex.h"

struct GeometryData
{
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	GeometryData() : vertices(0), numVertices(0), indices(0), numIndices(0)
	{

	}

	GLsizeiptr VertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr IndexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}
	GLsizeiptr TotalBufferSize() const
	{
		return IndexBufferSize() + VertexBufferSize();
	}

	void CleanUp()
	{
		delete[] vertices;
		delete[] indices;
		numVertices = numIndices = 0;
	}
};