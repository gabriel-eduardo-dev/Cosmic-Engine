#include "Window.hpp"
#include <stdexcept>


Window::Window()
	: glfw_window {nullptr}, window_width {800}, window_height {600}, title {"Cosmic"}, fullscreen {false}, vsync {true}, mssa4x {true}
{
	init_window();
}

Window::Window(u32 width, u32 height, std::string title, bool fullscreen, bool vsync, bool mssa4x)
	: glfw_window {nullptr}, window_width {width}, window_height {height}, title {title}, fullscreen {fullscreen}, vsync {vsync}, mssa4x {mssa4x} 
{
	init_window();
}

Window::~Window()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
	printf("Window closed...\n");
}

void Window::init_window()
{
	printf("Creating window...\n");

	if (!glfwInit())
	{
		this->~Window();
		throw std::runtime_error("FAILED TO INITIALIZE GLFW...\n");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	if (mssa4x) {
		glfwWindowHint(GLFW_SAMPLES, 4);
	}

	if (fullscreen) {
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfw_window = glfwCreateWindow(window_width, window_height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	} else {
		glfw_window = glfwCreateWindow(window_width, window_height, title.c_str(), nullptr, nullptr);
	}
	if (!glfw_window)
	{
		this->~Window();
		throw std::runtime_error("FAILED TO CREATE WINDOW...\n");
	}

	glfwMakeContextCurrent(glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		this->~Window();
		throw std::runtime_error("FAILED TO LOAD GLAD...\n");
	}
	glViewport(0, 0, window_width, window_height);
	if (vsync) {
		glfwSwapInterval(1);
	} else {
		glfwSwapInterval(0);
	}
	if (mssa4x) {
		glEnable(GL_MULTISAMPLE);
	}
	// center window
	const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(glfw_window,
				  vid_mode->width / 2 - window_width / 2, 
				  vid_mode->height / 2 - window_height / 2);

	install_main_callbacks();

	printf("Window created successfully...\n");
}

void Window::install_main_callbacks()
{
	glfwSetKeyCallback(glfw_window, Input::Callback::key_callback);
	glfwSetCursorPosCallback(glfw_window, Input::Callback::cursor_callback);
	glfwSetMouseButtonCallback(glfw_window, Input::Callback::mouse_buttom_callback);
	glfwSetScrollCallback(glfw_window, Input::Callback::mouse_scroll_callback);
	glfwSetFramebufferSizeCallback(glfw_window, Input::Callback::frame_buffer_size_callback);
	glfwSetErrorCallback(Input::Callback::error_callback);
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(glfw_window);

	// INFO: Get fps and ms
	current_time = glfwGetTime();
	delta = current_time - previuos_time;
	frame_count += 1 ;
	if (delta >= 1.0 / 30.0)
	{
		fps = (1.0 / delta) * frame_count;
		ms = (delta / frame_count) * 1000;

		previuos_time = current_time;
		frame_count = 0;
	}
}
