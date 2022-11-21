#include "App3.hpp"

namespace App3
{
	Window window;
		
	void run()
	{
		window.init();
		window.set_clear_color(Color{32,32,32});
		
		stbi_set_flip_vertically_on_load(true);
		i32 width, height, nrChannels;
		uchar *data = stbi_load("resources/images/container.jpg", &width, &height, &nrChannels, 0); 

		uint texture, texture2;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);

		data = stbi_load("resources/images/awesomeface.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		f32 vertices[] = {
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};
		uint indices[] = {
			0, 1, 3, 
		    1, 2, 3,
		};
		f32 texture_cords[] = {
			1.0f, 1.0f, 0.0,
			1.0f, 0.0f, 0.0,
			0.0f, 0.0f, 0.0,
			0.0f, 1.0f, 0.0,
		};
		
		Shader shader("resources/shaders/texture.vert", "resources/shaders/texture.frag");
		VAO vao;
		VBO vbo1, vbo2;
		EBO ebo;

		vao.bind();
		vbo1.buffer_data(vertices, sizeof(vertices), GL_STATIC_DRAW);
		vao.link_vbo(vbo1, 0);

		vbo2.buffer_data(texture_cords, sizeof(texture_cords), GL_STATIC_DRAW);
		vao.link_vbo(vbo2, 2);

		ebo.buffer_data(indices, sizeof(indices), GL_STATIC_DRAW);
		ebo.unbind();
		vao.unbind();

		shader.use();
		shader.set_int("texture1", 0);
		shader.set_int("texture2", 1);

		while (window.is_open()) {
			window.clear();

			if (Keyboard::is_key_release(GLFW_KEY_ESCAPE)) {
				window.close();
			}
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);

			shader.use();
			vao.bind();
			ebo.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			ebo.unbind();
			vao.unbind();

			window.update();
		}
	}
}
