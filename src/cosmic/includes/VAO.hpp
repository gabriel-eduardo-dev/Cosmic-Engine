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
		void link_vbo(VBO& vbo, UINT32 layout, i16 size, u16 stride, u16 pointer);
		void bind() const;
		void unbind() const;
		void destroy() const;
};

#endif
