#pragma once

#include <iostream>
#include <GL/glew.h>

class Buffer
{
public:
	Buffer(void)
	{
		glGenBuffers(1, &m_bufferID);
	}
	~Buffer(void)
	{
		glDeleteBuffers(1, &m_bufferID);
	}
	template<typename _Ty>
	void Init(uint32_t size, _Ty* data, GLenum usage, GLenum point)
	{
		Bind(point);
		glBufferData(point, size, data, usage);
	}
	template<typename _Ty>
	void SubData(uint32_t offset, uint32_t size, _Ty* data, GLenum point)
	{
		glBufferSubData(point, offset, size, data);
	}
	inline
		const uint32_t BufferID(void) const noexcept
	{
		return m_bufferID;
	}
	inline
		void Bind(GLenum point) const
	{
		glBindBuffer(point, m_bufferID);
	}
protected:
	uint32_t m_bufferID;
};