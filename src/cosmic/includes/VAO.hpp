#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>
#include "Types.hpp"
#include "VBO.hpp"

class VAO 
{
	public:
		
		UINT32 ID;

		VAO();
		~VAO();

		void link_vbo(VBO& vbo, UINT32 layout);
		void bind();
		void unbind();
		void destroy();
};

#endif
