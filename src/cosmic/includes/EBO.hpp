#ifndef EBO_HPP
#define EBO_HPP

#include <glad/glad.h>
#include "Types.hpp"

class EBO
{
	public:

		GLuint ID;
		EBO();
		EBO(UINT32* data, GLsizeiptr size, GLenum mode);
		~EBO();

		void buffer_data(UINT32* data, GLsizeiptr size, GLenum mode);
		void bind();
		void unbind();
		void destroy();
};

#endif
