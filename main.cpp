#include <iostream>

#include "Window.h"

static constexpr unsigned int STND_WIDTH = 800;
static constexpr unsigned int STND_HEIGHT = 600;
static long settings = 0x0;

// USER SETTINGS
static constexpr long PRINT_HELP_BIT = 0x1;
static constexpr long OBJ_LOADED_BIT = 0x2;
static constexpr long DEBUG_MODE_BIT = 0x4;

// Other constants
static constexpr int MAX_NUM_USAGE = 6;
static const std::string TEST_OBJ = "bunny.obj";


inline std::string printUsageStatement() {
	std::string usage = "===========\nUSAGE\n===========\n";
	usage += "\t [-h] [-w width height] obj\n";
	return usage;

}

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
	glClearColor(0, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char* argv[]) {
	std::string objToLoad = TEST_OBJ;
	int width = STND_WIDTH;
	int height = STND_HEIGHT;

	if (argc > MAX_NUM_USAGE) {
		std::cout << "Error: Number of given arguments not supported!\n";
		std::cout << printUsageStatement << std::endl;
		exit(EXIT_FAILURE);
	}

	// Parse user usage arguments
	// For now only deals with reading one scene object file
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'h':
				settings |= PRINT_HELP_BIT;
				break;
			case 'w':
				width = atoi(argv[i + 1]);
				height = atoi(argv[i + 2]);
				// move to next option
				i += 2;
				break;
			}

		}
		// Assuming object name is a file name
		else {
			objToLoad = std::string(argv[i]);
		}
	}

	// Deal with settings
	if (settings & PRINT_HELP_BIT)
		std::cout << printUsageStatement();

	std::cout << "Object to view: " << objToLoad << std::endl;

	// Make sure to make the window BEFORE initializing GLAD
	Window mainWindow = Window(width, height);

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