#include "Window.h"

Window::Window() {
	width = 800;
	height = 600;
	windowptr = initGLFWWindowSettings(width, height);
	initGLFWcallbacks();
}

Window::~Window() {
	if (windowptr != nullptr) {
		glfwTerminate();
		windowptr = nullptr;
	}
}

GLFWwindow* Window::initGLFWWindowSettings(int width, int height) {
	// Initializes GLFW library
	glfwInit();

	// Establishes the version type of OpenGL (3.3 core)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	return window;
}

GLFWwindow* Window::getWindowptr() const {
	return windowptr;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, 
	int height) {
	glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, 
	int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			std::cout << "Closing window\n";
			glfwSetWindowShouldClose(window, true);
			break;
		}
	}
}

void Window::initGLFWcallbacks() {
	//glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(windowptr, key_callback);
	glfwSetFramebufferSizeCallback(windowptr, framebuffer_size_callback);
}

void Window::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Check for events and swap buffers
	glfwSwapBuffers(windowptr);
	glfwPollEvents(); // LOOK THIS UP LATER
}
