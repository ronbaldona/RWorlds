#include "Window.h"
#include "Shader.h"

#include "OBJObject.h"

namespace {
	// TODO: CLEAN UP BY ADDING SIMPLE FILE LOADING SYSTEM
	std::string objPath = "Models/bunny.obj";
	// test objects
	Object* testObj;
	Skybox* skybox;

	Shader* skyboxShader;
	Shader* testShader;

	// Camera/Window variables
	int wWidth, wHeight;
	Camera mainCam;
	glm::mat4 view;
	glm::mat4 projection;

	// Trackball mode variables
	bool lmbPressed = false;
	double oldPos[2];
	glm::vec3 oldPosVec;

	// FPS camera mode variables
	glm::vec2 lastCursorPos;

	// Modes
	enum CAMERA_MODES{ OBJECT_MODE, FPS_MODE };
	int CURR_CAM_MODE = OBJECT_MODE;
	int NUM_CAM_MODES = 2;
}

/// <summary>
/// Changes xpos and ypos in window space where origin is at the upper left
/// corner to the center of the screen. Normalizes coordinates based on
/// smallest dimension of window
/// </summary>
/// <param name="xpos"> x position of cursor. A return parameter </param>
/// <param name="ypos"> y position of cursor. A return parameter </param>
inline void cursorPosChangeBasis(double& xpos, double& ypos) {
	double smallDim = (wWidth > wHeight) ? wHeight : wWidth;
	xpos = (xpos - (double)(0.5 * wWidth)) / (double)(0.5 * smallDim);
	ypos = ((double)(0.5 * wHeight) -  ypos) / (double)(0.5 * smallDim);
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
	wWidth = 800;
	wHeight = 600;

	std::cout << "Initializing window of size " << wWidth << " x ";
	std::cout << wHeight << std::endl;

	windowptr = initGLFWWindowSettings(wWidth, wHeight);
	initGLFWcallbacks();
	view = mainCam.getViewMat();
	projection = mainCam.getProjMat(wWidth, wHeight);

}

Window::~Window() {
	if (windowptr != nullptr) {
		glfwTerminate();
		windowptr = nullptr;
	}
}

Window::Window(int _width, int _height) {
	wWidth = _width;
	wHeight = _height;

	std::cout << "Initializing window of size " << wWidth << " x ";
	std::cout << wHeight << std::endl;

	windowptr = initGLFWWindowSettings(wWidth, wHeight);
	initGLFWcallbacks();
	view = mainCam.getViewMat();
	projection = mainCam.getProjMat(wWidth, wHeight);
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

	lastCursorPos = glm::vec2(0.5f * width, 0.5f * height);

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
	//testObj = new OBJObject(objPath.c_str());
	testObj = new Model(objPath.c_str());

	skybox = new Skybox();

	// Initialize shaders
	testShader = new Shader("Shaders/test.vert", "Shaders/test.frag");
	skyboxShader = new Shader("Shaders/Skybox.vert", "Shaders/Skybox.frag");
}

void Window::cleanUpScene() {
	// Clean up models
	delete testObj;

	delete skybox;

	// Clean up shaders
	testShader->deleteShader();
	delete testShader;
	skyboxShader->deleteShader();
	delete skyboxShader;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, 
	int height) {
	wWidth = width;
	wHeight = height;
	lastCursorPos = glm::vec2(0.5f * width, 0.5f * height);
	projection = mainCam.getProjMat(width, height);
	glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, 
	int action, int mods) {
	// TODO: Add caps lock check
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			std::cout << "Closing window\n";
			glfwSetWindowShouldClose(window, true);
			return;
		case GLFW_KEY_R:
			testObj->reset();
			break;
		case GLFW_KEY_UP:
			testObj->translate(0, 1.0f, 0);
			break;
		case GLFW_KEY_DOWN:
			testObj->translate(0, -1.0f, 0);
			break;
		case GLFW_KEY_LEFT:
			testObj->translate(-1.0f, 0, 0);
			break;
		case GLFW_KEY_RIGHT:
			testObj->translate(1.0f, 0, 0);
			break;
		case GLFW_KEY_C:
			CURR_CAM_MODE = ++CURR_CAM_MODE % NUM_CAM_MODES;
			std::cout << "CAM MODE: " << CURR_CAM_MODE << std::endl;
			if (CURR_CAM_MODE == FPS_MODE)
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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

	if (CURR_CAM_MODE == FPS_MODE) {
		mainCam.rotateCamFromMouseMove((float)(lastCursorPos.x - xpos),
			                           (float)(lastCursorPos.y - ypos));
		view = mainCam.getViewMat();
		lastCursorPos = glm::vec2((float)xpos, (float)ypos);
	}



	//std::cout << "Cursor position: " << xpos << " " << ypos << std::endl;
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action,
	int mods) {
	//TODO
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
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
	testObj->translate(glm::vec3(0, 0, -yoffset));
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
	skybox->draw(*skyboxShader, view, projection);

	// Check for events and swap buffers
	glfwSwapBuffers(windowptr);
	glfwPollEvents(); // LOOK THIS UP LATER
}
