#include "App2.hpp"
#include "Input.hpp"

namespace App2 {

	void run() {

	Window window;
	
		F32 vertices[] = {
			-1.0, 1.0, 0.0, 
			1.0,  1.0, 0.0,
			-1.0, -1.0, 0.0,
			1.0, -1.0, 0.0,
		};

		UINT32 indices[] = {
			0, 1, 2,
			2, 3, 1,
		};

		glm::vec2 resolution = glm::vec2(800, 600);
		Shader shader_program("shaders/mandelbroat.vert", "shaders/mandelbroat.frag");
		VAO vao;
		VBO vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);
		vao.link_vbo(vbo, 0);
		EBO ebo(indices, sizeof(indices), GL_STATIC_DRAW);
		vao.unbind();

		window.set_vsync(false);

			while (window.is_open()) {
			window.clear();
			if (Keyboard::is_key_release(GLFW_KEY_ESCAPE)) {
				window.close();
			} vao.bind();
			ebo.bind();
			shader_program.use();
			shader_program.set_vec2("resolution", resolution); 
			shader_program.set_float("time", glfwGetTime());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
			ebo.unbind();
			vao.unbind();

			window.update();
		}
	}
}