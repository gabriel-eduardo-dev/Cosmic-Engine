#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>
#include <array>
#include <iostream>

#include "Vectors.hpp"

namespace Input
{
	namespace Data 
	{
		extern std::array<bool, GLFW_KEY_LAST> key_down_data;
		extern std::array<bool, GLFW_KEY_LAST> key_pressed_data;
		extern std::array<bool, GLFW_KEY_LAST> key_release_data;
		extern std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_buttom_pressed_data;
		extern std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_buttom_release_data;
		extern vec2d mouse_pos;
		extern vec2d mouse_scroll;
	}
	namespace Callback
	{
		void key_callback(GLFWwindow *window, int key, int scan_code, int action, int mods);
		void cursor_callback(GLFWwindow *window, double x_pos, double y_pos);
		void mouse_buttom_callback(GLFWwindow *window, int buttom, int action, int mods);
		void mouse_scroll_callback(GLFWwindow *window, double x_offset, double y_offset);
		void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
		void error_callback(int, const char* error);
	}
}

namespace Keyboard
{
    bool is_key_down(int key);
	bool is_key_release(int key);
	bool is_key_pressed(int key);
}

namespace Mouse
{
    bool is_button_down(int mouse_buttom);
	bool is_buttom_release(int mouse_buttom);
	bool is_buttom_pressed(int mouse_buttom);
	inline vec2d &get_pos()
	{
		return Input::Data::mouse_pos;
	}
	inline double get_x()
	{
		return Input::Data::mouse_pos.x;
	}
	inline double get_y()
	{
		return Input::Data::mouse_pos.y;
	}
}

#endif
