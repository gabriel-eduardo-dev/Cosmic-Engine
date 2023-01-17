#include "Camera.hpp"
#include "Input.hpp"
#include <GLFW/glfw3.h>


Camera::Camera(int32_t width, int32_t height, glm::vec3 position)
	:  position {position}, width {width}, height {height}, first_click {true}
{

}

void Camera::update(float fov_deg, float near_plane, float far_plane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0);
	glm::mat4 projection = glm::mat4(1.0);
	
	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(fov_deg), static_cast<float>((float)width / height), near_plane, far_plane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow* window)
{
	if (Keyboard::is_key_down(GLFW_KEY_W))
	{
		position += speed * orientation;
	}
	if (Keyboard::is_key_down(GLFW_KEY_A))
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (Keyboard::is_key_down(GLFW_KEY_S))
	{
		position += speed * -orientation;
	}
	if (Keyboard::is_key_down(GLFW_KEY_D))
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (Keyboard::is_key_down(GLFW_KEY_SPACE))
	{
		position += speed * up;
	}
	if (Keyboard::is_key_down(GLFW_KEY_LEFT_SHIFT))
	{
		position += speed * -up;
	}

	if (Mouse::is_button_down(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (first_click)
		{
			glfwSetCursorPos(window, (width / 2.0), (height / 2.0));
			first_click = false;
		}

		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotx = sensitivy * static_cast<float>(mouseY - (height / 2.0)) / height;
		float roty = sensitivy * static_cast<float>(mouseX - (width  / 2.0)) / width;

		glm::vec3 new_orientation = glm::rotate(orientation, glm::radians(-rotx), glm::normalize(glm::cross(orientation, up)));

		if (fabs(glm::angle(new_orientation, up) - glm::radians(90.0)) <= glm::radians(85.0))
		{
			orientation = new_orientation;
		}
		orientation = glm::rotate(orientation, glm::radians(-roty), up);

		glfwSetCursorPos(window, (width / 2.0), (height / 2.0));
	}
	else if (Mouse::is_buttom_release(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		first_click = true;
	}
}
