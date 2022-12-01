#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"

class Renderer 
{
	public:

		Renderer();
		~Renderer();

		void Draw(const VAO &vao, const EBO& ebo, const Shader& shader) const;
};

#endif
