#include <iostream>

#include "Window.h"

// Initializes GLAD for OpenGL function uses
int initOpenGLGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL version is " << glGetString(GL_VERSION) << std::endl;

	return EXIT_SUCCESS;
}

// Initializes various OpenGL settings
void initOpenGLSettings() {
	glViewport(0, 0, 800, 600);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char* argv[]) {
	// Make sure to make the window BEFORE initializing GLAD
	Window mainWindow = Window();

	// Initialize GLAD
	if (initOpenGLGlad() == EXIT_FAILURE)
		return EXIT_FAILURE;

	// Other OpenGL settings
	initOpenGLSettings();

	// Main render loop
	while (!glfwWindowShouldClose(mainWindow.getWindowptr())) {
		mainWindow.render();
	}

	return EXIT_SUCCESS;
}