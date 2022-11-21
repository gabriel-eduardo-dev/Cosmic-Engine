#include "EBO.hpp"

EBO::EBO()
{
	glGenBuffers(1, &ID);
}

EBO::EBO(UINT32* data, GLsizeiptr size, GLenum mode)
{
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode);
	unbind();
}

void EBO::buffer_data(UINT32 *data, GLsizeiptr size, GLenum mode)
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode);
	unbind();
}

EBO::~EBO()
{
	glDeleteBuffers(1, &ID);
}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy()
{
	glDeleteBuffers(1, &ID);
}
