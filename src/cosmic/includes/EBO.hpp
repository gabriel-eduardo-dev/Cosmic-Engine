#ifndef EBO_HPP
#define EBO_HPP

#include <glad/glad.h>
#include "Types.hpp"
#include <iostream>

class EBO
{
	public:

		GLuint ID;
		size_t total_elements;

		EBO();
		EBO(UINT32* data, GLsizeiptr size, GLenum mode);
		~EBO();

		void buffer_data(UINT32* data, GLsizeiptr size, GLenum mode);
		void bind() const;
		void unbind() const;
		void destroy() const;
};

#endif
