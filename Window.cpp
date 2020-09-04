#include "Window.h"
#include "Shader.h"

#include "OBJObject.h"

namespace {
	std::string objPath = "Models/bunny.obj";
	// test objects
	Object* testObj;
	Shader* testShader;

	// Camera/Window variables
	int width, height;
	Camera mainCam;
	glm::mat4 view;
	glm::mat4 projection;

}

Window::Window() {
	width = 800;
	height = 600;

	std::cout << "Initializing window of size " << width << " x ";
	std::cout << height << std::endl;

	windowptr = initGLFWWindowSettings(width, height);
	initGLFWcallbacks();
	view = mainCam.getViewMat();
	projection = mainCam.getProjMat(width, height);

}

Window::~Window() {
	if (windowptr != nullptr) {
		glfwTerminate();
		windowptr = nullptr;
	}
}

Window::Window(int _width, int _height) {
	width = _width;
	height = _height;

	std::cout << "Initializing window of size " << width << " x ";
	std::cout << height << std::endl;

	windowptr = initGLFWWindowSettings(width, height);
	initGLFWcallbacks();
	view = mainCam.getViewMat();
	projection = mainCam.getProjMat(width, height);
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
	std::cout << glfwGetVersionString() << std::endl;
	return window;
}

GLFWwindow* Window::getWindowptr() const {
	return windowptr;
}

void Window::setObjToView(const std::string& path) {
	objPath = path;
}

void Window::initializeScene() {
	// Initialize objects
	testObj = new OBJObject(objPath.c_str());

	// Initialize shaders
	testShader = new Shader("Shaders/test.vert", "Shaders/test.frag");
}

void Window::cleanUpScene() {
	// Clean up models
	delete testObj;

	// Clean up shaders
	delete testShader;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, 
	int height) {
	projection = mainCam.getProjMat(width, height);
	glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, 
	int action, int mods) {
	if (action == GLFW_PRESS) {
		if (mods != GLFW_MOD_SHIFT) {
			switch (key) {
			case GLFW_KEY_ESCAPE:
				std::cout << "Closing window\n";
				glfwSetWindowShouldClose(window, true);
				break;
			case GLFW_KEY_S:
				testObj->scale(glm::vec3(1.1f));
				break;
			default:
				std::cout << "No action mapped to this key.\n";
				break;
			}
		}
	}
}

void Window::initGLFWcallbacks() {
	//glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(windowptr, key_callback);
	glfwSetFramebufferSizeCallback(windowptr, framebuffer_size_callback);
}

void Window::render() {
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	testObj->draw(*testShader, view, projection);

	// Check for events and swap buffers
	glfwSwapBuffers(windowptr);
	glfwPollEvents(); // LOOK THIS UP LATER
}
