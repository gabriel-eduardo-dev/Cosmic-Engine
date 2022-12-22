#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"
#include "Window.hpp"
#include "Input.hpp"

class Camera 
{
	public:

		Camera(int32_t width, int32_t height, glm::vec3 position);

		void update(float fov_deg, float near_plane, float far_plane, Shader& shader, const char* uniform);
		void inputs(GLFWwindow* window);

	private:

		glm::vec3 position;
		glm::vec3 orientation = glm::vec3(0.0, 0.0, -1.0);
		glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

		int32_t width;
		int32_t height;

		float speed = 0.5;
		float sensitivy = 100.0;

		bool first_click;
};

#endif
