#include "VAO.hpp"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
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

void VAO::link_vbo(VBO& vbo, UINT32 layout, i16 size, u16 stride, u16 pointer)
{
	vbo.bind();
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride * sizeof(F32), (GLvoid*)(pointer * sizeof(F32)));
	vbo.unbind();
}

void VAO::bind() const
{
	glBindVertexArray(ID);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

void VAO::destroy() const
{
	glDeleteVertexArrays(1, &ID);
}
