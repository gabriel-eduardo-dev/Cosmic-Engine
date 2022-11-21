#include "App.hpp"

namespace App {
	void run() {
		
		Window window;

		F32 vertices[] =
		{
			-0.5,  0.5, 0.0, 
			 0.5,  0.5, 0.0,
			-0.5, -0.5, 0.0,
			 0.5, -0.5, 0.0,

			-0.5,  0.5, -1.0, 
			 0.5,  0.5, -1.0,
			-0.5, -0.5, -1.0,
			 0.5, -0.5, -1.0,
		};

		UINT32 indices[] =
		{
			0, 1, 2,
			2, 1, 3,

			4, 5, 6,
			6, 7, 5,

			0, 2, 6,
			0, 4, 6,

			3, 7, 1,
			1, 5, 7,

			0, 1, 4,
			1, 4, 5,

			3, 6, 7,
			3, 2, 6,
		};

		Shader shader_program("shaders/default.vert", "shaders/default.frag");

		VAO vao;

		VBO vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);
		vao.link_vbo(vbo, 0);

		EBO ebo(indices, sizeof(indices), GL_STATIC_DRAW);

		vao.unbind();

		window.set_clear_color(Color{29,29,29});

		Camera camera(800, 600, glm::vec3(0.0, 00.0, 50.0));

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window.get_handle(), true);
		ImGui_ImplOpenGL3_Init("#version 460");

		bool debug = false;
		bool point = false;
		bool rotate = false;
		glm::vec3 scales = glm::vec3(1.0);
		glm::vec2 resolution = glm::vec2(800.0, 600.0);
		glm::vec3 translations[1000];

		while (window.is_open())
		{
			window.update();
			window.clear();
			camera.inputs(window.get_handle());

			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::rotate(trans, window.get_time(), glm::vec3(0.0f, 0.0f, 3.0f));

			u16 index = 0;
			f32 scale = (2.0f + (float)sinf(glfwGetTime()))*0.7f;

			for (int x = 0; x < 22; x += 2)
			{
				for (int y = 0; y < 22; y += 2)
				{
					for (int z = 0; z < 16; z += 2)
					{
						float block_scale = (x + y + z) / 7.0;

						float scatter = sinf(block_scale + static_cast<float>(glfwGetTime() * 3.14));

						glm::vec3 trans;
						trans.x = static_cast<float>(x - 22.0 / 3.0) * (scale / 2.0) + scatter;
						trans.y = static_cast<float>(y - 22.0 / 2.0) * (scale / 2.0) + scatter;
						trans.z = static_cast<float>(z - 15.0 / 3.0) * (scale / 2.0) + scatter;

						translations[index++] = trans;
					}
				}
			}

			if (Keyboard::is_key_pressed(GLFW_KEY_ESCAPE))
			{
				window.close();
			}
			if (debug) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame(); ImGui::NewFrame();
			vao.bind();
			ebo.bind();
			shader_program.use();
			shader_program.set_vec3("u_scales", scales);
			shader_program.set_vec2("u_resolution", resolution);
			shader_program.set_float("u_time", window.get_time());
			if (rotate)
				shader_program.set_mat4("transform", trans);
			else {
				shader_program.set_mat4("transform", glm::mat4(1.0));
			}
			for (u16 i = 0; i < 1000; ++i)
			{
				shader_program.set_vec3(("offsets[" + std::to_string(i) + "]").c_str(), translations[i]);
			}
			camera.update(45.0, 0.1, 100.0, shader_program, "u_cam_matrix");
			if (point) {
				glDrawElementsInstanced(GL_POINTS, 40, GL_UNSIGNED_INT, 0, 1000);
			} else {
				glDrawElementsInstanced(GL_TRIANGLES, 40, GL_UNSIGNED_INT, 0, 1000);
			}
			ebo.unbind();
			vao.unbind();

			ImGui::Begin("Cosmic");
			ImGui::Text("Hello Cosmic");
			ImGui::Checkbox("Debug", &debug);
			ImGui::Checkbox("Points", &point);
			ImGui::Checkbox("Rotate", &rotate);
			ImGui::SliderFloat("Scale x", &scales.x, -5.0, 5.0);
			ImGui::SliderFloat("Scale y", &scales.y, -5.0, 5.0);
			ImGui::SliderFloat("Scale z", &scales.z, -5.0, 5.0);
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}
}
