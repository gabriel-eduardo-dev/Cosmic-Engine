#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class Renderer 
{
	public:

		Renderer();
		~Renderer();

		void Draw(const VAO &vao, const EBO& ebo, const Shader& shader) const;
		void Draw(const VAO &vao, const EBO& ebo, const Texture &texture, const Shader& shader) const;
};

#endif
