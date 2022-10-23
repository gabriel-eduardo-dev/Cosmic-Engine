#include "VBO.hpp"

VBO::VBO(GLfloat* vertices, GLsizeiptr size, GLenum mode)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, mode);
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
