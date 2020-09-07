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

	// Trackball mode variables
	bool lmbPressed = false;
	double oldPos[2];
	glm::vec3 oldPosVec;
}

/// <summary>
/// Changes xpos and ypos in window space where origin is at the upper left
/// corner to the center of the screen. Normalizes coordinates based on
/// smallest dimension of window
/// </summary>
/// <param name="xpos"> x position of cursor. A return parameter </param>
/// <param name="ypos"> y position of cursor. A return parameter </param>
inline void cursorPosChangeBasis(double& xpos, double& ypos) {
	double smallDim = (width > height) ? height : width;
	xpos = (xpos - (double)(0.5 * width)) / (double)(0.5 * smallDim);
	ypos = ((double)(0.5 * height) -  ypos) / (double)(0.5 * smallDim);
}

/// <summary>
/// Projects cursor onto unit sphere superimposed onto window
/// </summary>
/// <param name="xpos"> x position of cursor before basis change </param>
/// <param name="ypos"> y position of cursor before basis change </param>
/// <returns></returns>
inline glm::vec3 projectCursorOntoSphere(double xpos, double ypos) {
	cursorPosChangeBasis(xpos, ypos);

	// clip 2d vector at edge of unit circle on xy plane
	double d = sqrt(xpos * xpos + ypos * ypos);
	if (d > 1) {
		xpos /= d;
		ypos /= d;
		d = 1;
	}
	
	// Now clip 3d vector at edge of unit hemisphere 
	return glm::vec3(xpos, ypos, sqrt(1 - d));
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

	// More settings
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	else
		std::cout << "Raw mouse motion not supported\n";

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
	// TODO: Add caps lock check
	if (action == GLFW_PRESS) {
		// both lower and upper case
		if (key == GLFW_KEY_ESCAPE) {
			std::cout << "Closing window\n";
			glfwSetWindowShouldClose(window, true);
			return;
		}
		if (key == GLFW_KEY_R) {
			testObj->reset();
		}

		// lower case
		if (mods != GLFW_MOD_SHIFT) {
			switch (key) {
			case GLFW_KEY_S:
				testObj->scale(glm::vec3(0.9f));
				break;
			default:
				break;
			}
		}
		// upper case
		else {
			switch (key) {
			case GLFW_KEY_S:
				testObj->scale(glm::vec3(1.1f));
				break;
			default:
				break;
			}
		}
	}

}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, 
	double ypos) {
	//std::cout << "Cursor position: " << xpos << " " << ypos << std::endl;

	// Get new pos in new basis
	if (lmbPressed) {
		// Project both new and old positions to unit sphere
		glm::vec3 newPosVec = projectCursorOntoSphere(xpos, ypos);

		// Retrieve angle and axis then rotate
		glm::vec3 axis = glm::cross(oldPosVec, newPosVec);
		//std::cout << "Axis of rotation: " << axis.x << " " << axis.y << " " << axis.z << std::endl;
		if (length(axis) > 1e-4f) {
			float dot = glm::dot(oldPosVec, newPosVec) / 
				(glm::length(oldPosVec) * glm::length(newPosVec));
			float angle = acosf(dot) / 15.0f;

			testObj->rotate(angle, axis);
		}
	}


	//std::cout << "Cursor position: " << xpos << " " << ypos << std::endl;
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action,
	int mods) {
	//TODO
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		// TODO: OPTIMIZE THIS
		if (action == GLFW_PRESS) {
			// Set cursor and motion modes
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Get cursor position and unit sphere projection on button press
			lmbPressed = true;
			glfwGetCursorPos(window, oldPos, &oldPos[1]);
			oldPosVec = projectCursorOntoSphere(oldPos[0], oldPos[1]);

		}
		else if (action == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			lmbPressed = false;
		}
	}
}

void Window::scroll_callback(GLFWwindow* window, double xoffset,
	double yoffset) {
	//TODO
}

void Window::initGLFWcallbacks() {
	//glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(windowptr, key_callback);
	glfwSetFramebufferSizeCallback(windowptr, framebuffer_size_callback);
	glfwSetCursorPosCallback(windowptr, cursor_position_callback);
	glfwSetMouseButtonCallback(windowptr, mouse_button_callback);
	glfwSetScrollCallback(windowptr, scroll_callback);
}

void Window::render() {
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	testObj->draw(*testShader, view, projection);

	// Check for events and swap buffers
	glfwSwapBuffers(windowptr);
	glfwPollEvents(); // LOOK THIS UP LATER
}
