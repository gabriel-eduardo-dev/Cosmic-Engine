#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Types.hpp"
#include "Input.hpp"
#include "Vectors.hpp"
#include "Color.hpp"

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6

class Window {
	
	public:
	
		// INFO: Constructors
		Window(u32 width, u32 height, std::string title, bool fullscreen, bool vsync, bool mssa4x);
		Window();
		~Window();
		
		// INFO: Functions
		inline bool is_open();
		inline void clear();
		inline void close();
		inline bool is_fullscreen();
		inline bool is_vsync();
		void update();

		// INFO: Geters
		inline GLFWwindow* get_handle() const;
		inline std::string get_title();
		inline f64 get_fps();
		inline f64 get_ms();
		inline f32 get_time();

		// INFO: Setters;
		inline void set_title(const std::string& new_title);
		inline void set_clear_color(const Color& color);
		inline void set_vsync(bool state);
		inline void set_time(f32 time);

	private:

		// INFO: Private functions to initialize window
		void init_window();
		void install_main_callbacks();

		// INFO: Variables
		GLFWwindow* glfw_window;	
			
		u32 window_width;
		u32 window_height;
		std::string title;
		bool fullscreen;
		bool vsync;
		bool mssa4x;

		// INFO: FPS Variables
		f32 fps;
		f32 ms;
		f32 previuos_time;
		f32 current_time;
		f32 delta;
		u32 frame_count;
};

// INFO: Inline functions

inline f32 Window::get_time()
{
	return static_cast<f32>(glfwGetTime());
}

inline void Window::set_time(f32 time)
{
	glfwSetTime(time);
}

inline void Window::close()
{
	glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
}

inline bool Window::is_open()
{
	return !glfwWindowShouldClose(glfw_window);
}

inline void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline std::string Window::get_title()
{
	return title;
}

inline void Window::set_title(const std::string& new_title)
{
	glfwSetWindowTitle(glfw_window, new_title.c_str());
}

inline void Window::set_clear_color(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

inline GLFWwindow* Window::get_handle() const
{
	return glfw_window;
}

inline bool Window::is_vsync()
{
	return vsync;
}

inline void Window::set_vsync(bool state)
{
	(state) ? glfwSwapInterval(1) : glfwSwapInterval(0);
}

inline bool Window::is_fullscreen()
{
	return fullscreen;
}

inline f64 Window::get_fps()
{
	return fps;
}

inline f64 Window::get_ms()
{
	return ms;
}

#endif
