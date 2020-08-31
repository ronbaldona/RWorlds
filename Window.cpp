#include "Window.h"
#include "Shader.h"

#include "OBJObject.h"

namespace {
	// test objects
	static Object* testObj;
	static Shader* testShader;


}

Window::Window() {
	width = 800;
	height = 600;

	std::cout << "Initializing window of size " << width << " x ";
	std::cout << height << std::endl;

	windowptr = initGLFWWindowSettings(width, height);
	initGLFWcallbacks();
}

Window::~Window() {
	if (windowptr != nullptr) {
		glfwTerminate();
		windowptr = nullptr;
	}
}

Window::Window(int width, int height) {
	this->width = width;
	this->height = height;
	windowptr = initGLFWWindowSettings(width, height);
	initGLFWcallbacks();
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

void Window::initializeScene() {
	testObj = new OBJObject("Models/bunny.obj");
}

void Window::cleanUpScene() {
	delete testObj;
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
