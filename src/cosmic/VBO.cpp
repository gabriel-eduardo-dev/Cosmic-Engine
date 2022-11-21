#include "VBO.hpp"

VBO::VBO()
{
	glGenBuffers(1, &ID);
}

VBO::VBO(GLfloat* data, GLsizeiptr size, GLenum mode)
{
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}

void VBO::buffer_data(F32* data, GLsizeiptr size, GLenum mode)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, mode);
	unbind();
}

VBO::~VBO()
{
	glDeleteBuffers(1, &ID);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy()
{
	glDeleteBuffers(1, &ID);
}
