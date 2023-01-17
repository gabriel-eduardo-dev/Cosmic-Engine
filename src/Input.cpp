#include "Input.hpp"

namespace Input
{
	namespace Data 
	{
		std::array<bool, GLFW_KEY_LAST> key_down_data;
		std::array<bool, GLFW_KEY_LAST> key_pressed_data;
		std::array<bool, GLFW_KEY_LAST> key_release_data;
		std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_buttom_pressed_data;
		std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_buttom_release_data;
		vec2d mouse_pos;
		vec2d mouse_scroll;
	}
	namespace Callback 
	{
		void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods)
		{	
			(void)window;
			(void)scan_code;
			(void)mods;

			if (key >= 0 && key < GLFW_KEY_LAST)
			{
				if (action == GLFW_PRESS || action == GLFW_REPEAT)
				{
					Data::key_down_data[key] = true;
				} else {
					Data::key_down_data[key] = false;
				}
				Data::key_pressed_data[key] = action == GLFW_PRESS;
				Data::key_release_data[key] = action == GLFW_RELEASE;
			}
		}
		void cursor_callback(GLFWwindow* window, double x_pos, double y_pos)
		{
			(void)window;

			Data::mouse_pos.x = x_pos;
			Data::mouse_pos.y = y_pos;
		}
		void mouse_buttom_callback(GLFWwindow* window, int buttom, int action, int mods)
		{
			(void)window;
			(void)mods;

			if (buttom >= 0 && buttom < GLFW_MOUSE_BUTTON_LAST)
			{
				Data::mouse_buttom_pressed_data[buttom] = action == GLFW_PRESS;
				Data::mouse_buttom_release_data[buttom] = action == GLFW_RELEASE;
			}
		}
		void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
		{
			(void)window;

			Data::mouse_scroll.x = static_cast<float>(x_offset);
			Data::mouse_scroll.y = static_cast<float>(y_offset);
		}

		void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
		{
			(void)window;

			glViewport(0, 0, width, height);	
		}
		
		void error_callback(int, const char* error)
		{
			LOG(error);
		}
	}
}

namespace Keyboard
{
	bool is_key_down(int key)
	{
		if (key >= 0 && key < GLFW_KEY_LAST)
		{
			return Input::Data::key_down_data[key];
		}
		return false;
	}
	bool is_key_release(int key)
	{
		if (key >= 0 && key < GLFW_KEY_LAST)
		{
			if (Input::Data::key_release_data[key])
			{
				Input::Data::key_release_data[key] = false;
				return true;
			}
		}
		return false;
	}
	bool is_key_pressed(int key)
	{
		if (key >= 0 && key < GLFW_KEY_LAST)
		{
			if (Input::Data::key_pressed_data[key])
			{
				Input::Data::key_pressed_data[key] = false;
				return true;
			}
		}
		return false;
	}
}

namespace Mouse
{
	bool is_button_down(int mouse_buttom)
	{
		if (mouse_buttom >= 0 && mouse_buttom < GLFW_MOUSE_BUTTON_LAST)
		{
			return Input::Data::mouse_buttom_pressed_data[mouse_buttom];
		}
		return false;
	}
	bool is_buttom_release(int mouse_buttom)
	{
		if (mouse_buttom >= 0 && mouse_buttom < GLFW_MOUSE_BUTTON_LAST)
		{
			if (Input::Data::mouse_buttom_release_data[mouse_buttom])
			{
				Input::Data::mouse_buttom_release_data[mouse_buttom] = false;
				return true;
			}
		}
		return false;
	}
	bool is_buttom_pressed(int mouse_buttom)
	{
		if (mouse_buttom >= 0 && mouse_buttom < GLFW_MOUSE_BUTTON_LAST)
		{
			if (Input::Data::mouse_buttom_pressed_data[mouse_buttom])
			{
				Input::Data::mouse_buttom_pressed_data[mouse_buttom] = false;
				return true;
			}
		}
		return false;
	}
}
