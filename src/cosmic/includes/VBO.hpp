#ifndef VBO_HPP
#define VBO_HPP

#include <glad/glad.h>
#include "Types.hpp"

class VBO 
{
	public:

		UINT32 ID;

		VBO(F32* vertices, GLsizeiptr size, GLenum type);
		~VBO();

		void bind();
		void unbind();
		void destroy();
};

#endif
