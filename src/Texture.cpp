#include "Texture.hpp"

Texture::Texture(const char* image, GLenum tex_type, GLenum slot, GLenum format, GLenum pixel_type)
	:type (tex_type)
{
	glGenTextures(1, &ID);

	glActiveTexture(slot);
	glBindTexture(tex_type, ID);

	glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	i32 width, height, numColCh;
	stbi_set_flip_vertically_on_load(true);

	uchar* data = stbi_load(image, &width, &height, &numColCh, 0);
	if (data)
	{
		glTexImage2D(tex_type, 0, format, width, height, 0, format, pixel_type, data);
		glGenerateMipmap(tex_type);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	unbind();
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::tex_unit(Shader& shader, const char* uniform, GLuint unit)
{
	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, uniform), unit);
}

void Texture::bind() const
{
	glBindTexture(type, ID);
}

void Texture::unbind() const
{
	glBindTexture(type, 0);
}

void Texture::destroy() const
{
	glDeleteTextures(1, &ID);
}
