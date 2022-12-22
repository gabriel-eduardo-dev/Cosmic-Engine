#include "Cosmic.hpp"

int main (int argc, char *argv[])
{
	Window window;
	window.init();
	window.set_clear_color(Color{32,32,32});

	glm::vec2 resolution = glm::vec2(800, 600);
	Shader shader_program("resources/shaders/mandelbroat.vert", "resources/shaders/mandelbroat.frag");
	VAO vao;
	vao.bind();
	VBO vbo(Polygons::Square::vertices, sizeof(Polygons::Square::vertices), GL_STATIC_DRAW);
	vao.link_vbo(vbo, 0);
	EBO ebo(Polygons::Square::indices, sizeof(Polygons::Square::indices), GL_STATIC_DRAW);
	vao.unbind();

	Renderer render;

	window.set_vsync(true);

	while (window.is_open()) {
		window.clear();
		if (Keyboard::is_key_release(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
		shader_program.use();
		shader_program.set_vec2("resolution", resolution); 
		shader_program.set_float("time", glfwGetTime());
		render.Draw(vao, ebo, shader_program);


		window.update();
	}
}
