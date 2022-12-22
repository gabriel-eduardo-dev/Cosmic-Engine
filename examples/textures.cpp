#include "Cosmic.hpp"

int main (int argc, char *argv[])
{
	Window window;
	window.init();
	window.set_clear_color(Color{32,32,32});
	
	Shader shader("resources/shaders/texture.vert", "resources/shaders/texture.frag");
	Texture texture("resources/images/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	
	VAO vao;
	VBO vbo1, vbo2;
	EBO ebo;

	vao.bind();
	vbo1.buffer_data(Polygons::Square::vertices, sizeof(Polygons::Square::vertices), GL_STATIC_DRAW);
	vao.link_vbo(vbo1, 0);

	vbo2.buffer_data(Polygons::Square::text_cords, sizeof(Polygons::Square::text_cords), GL_STATIC_DRAW);
	vao.link_vbo(vbo2, 2);

	ebo.buffer_data(Polygons::Square::indices, sizeof(Polygons::Square::indices), GL_STATIC_DRAW);
	ebo.unbind();
	vao.unbind();

	window.set_vsync(true);
	
	Renderer render;

	while (window.is_open()) {
		window.clear();

		if (Keyboard::is_key_release(GLFW_KEY_ESCAPE)) {
			window.close();
		}
		render.Draw(vao, ebo, texture, shader);
		
		window.update();
	}
}
