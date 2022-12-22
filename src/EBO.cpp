#include "EBO.hpp"

EBO::EBO()
	:total_elements(0)
{
	glGenBuffers(1, &ID);
}

EBO::EBO(UINT32* data, GLsizeiptr size, GLenum mode)
{
	total_elements = size / sizeof(UINT32);
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode);
	unbind();
}

void EBO::buffer_data(UINT32 *data, GLsizeiptr size, GLenum mode)
{
	total_elements = size / sizeof(UINT32);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode);
	unbind();
}

EBO::~EBO()
{
	glDeleteBuffers(1, &ID);
}

void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy() const
{
	glDeleteBuffers(1, &ID);
}
