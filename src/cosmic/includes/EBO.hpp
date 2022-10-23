#ifndef EBO_HPP
#define EBO_HPP

#include <glad/glad.h>
#include "Types.hpp"

class EBO
{
	public:

		GLuint ID;
		EBO(UINT32* indices, GLsizeiptr size, GLenum mode);
		~EBO();

		void bind();
		void unbind();
		void destroy();
};

#endif
