#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"
#include "Types.hpp"
#include "Shader.hpp"
#include "Defines.hpp"

class Texture 
{
	public:

		UINT32 ID;
		UINT32 type;
		i32 width, height, numColCh;

		Texture(const char* image, GLenum tex_type, GLenum slot, GLenum format, GLenum pixel_type);
		~Texture();

		void tex_unit(Shader& shader, const char* uniform, UINT32 unit);
		void bind() const;
		void unbind() const;
		void destroy() const;
};

#endif


