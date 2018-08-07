#pragma once
#include <GLEW/include/GL/glew.h>

namespace GLabs
{
	class Texture
	{
	public:
		Texture() :width(0), height(0), textureFormat(GL_RGB), imageFormat(GL_RGB),
			wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMax(GL_LINEAR), filterMin(GL_LINEAR)
		{
			glGenTextures(1, &textureID);
		}

		GLuint textureID;
		GLuint width, height;
		GLuint textureFormat;
		GLuint imageFormat;

		GLuint wrapS, wrapT;
		GLuint filterMax, filterMin;

		void Generate(GLuint p_width, GLuint p_height, unsigned char* data);
		void Bind() const;
	};
}