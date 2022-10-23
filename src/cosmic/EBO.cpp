#include "EBO.hpp"

EBO::EBO(UINT32* indices, GLsizeiptr size, GLenum mode)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, mode);
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
