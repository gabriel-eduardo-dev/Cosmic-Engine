#ifndef VBO_HPP
#define VBO_HPP

#include <glad/glad.h>
#include "Types.hpp"

class VBO 
{
	public:

		UINT32 ID;

		VBO();
		VBO(F32* data, GLsizeiptr size, GLenum mode);
		void buffer_data(F32* data, GLsizeiptr size, GLenum mode);
		~VBO();

		void bind();
		void unbind();
		void destroy();
};

#endif
