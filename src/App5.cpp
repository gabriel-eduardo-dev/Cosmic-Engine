#include "App5.hpp"

// code from: https://github.com/StanislavPetrovV/The-Planet-Sine

namespace App5 
{
	void run()
	{
		Window window;
		window.init();
		window.set_clear_color(Color{32,32,32});
		
		Shader shader("resources/shaders/App5.vert", "resources/shaders/App5.frag");

		VAO vao;
		VBO vbo;
		EBO ebo;

		vao.bind();
		vbo.buffer_data(Polygons::Square::vertices, sizeof(Polygons::Square::vertices), GL_STATIC_DRAW);
		vao.link_vbo(vbo, 0);
		vbo.unbind();

		ebo.buffer_data(Polygons::Square::indices, sizeof(Polygons::Square::indices), GL_STATIC_DRAW);
		ebo.unbind();
		vao.unbind();

		Renderer render;

		glm::vec2 uresolution = {800.0, 600.0};

		std::cout << ebo.total_elements << '\n';

		shader.use();
		shader.set_vec2("u_resolution", uresolution);

		while (window.is_open())
		{
			window.clear();

			if (Keyboard::is_key_release(KEY_ESCAPE))
			{
				window.close();
			}
			shader.use();
			shader.set_float("u_time", glfwGetTime());
			render.Draw(vao, ebo, shader);

			window.update();
		}

	}	
}
