#include "VAO.hpp"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
	bind();
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::link_vbo(VBO& vbo, UINT32 layout)
{
	vbo.bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}

void VAO::bind()
{
	glBindVertexArray(ID);
}

void VAO::unbind()
{
	glBindVertexArray(ID);
}

void VAO::destroy()
{
	glDeleteVertexArrays(1, &ID);
}
