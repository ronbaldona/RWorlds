/*
    Handles display window and events
	
	- RAB
 */
// TODO: Look into SINGLETON classes. Should this be a singleton?
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Object.h"

class Window {
	// Window dimensions
	int width, height;
	// Camera settings
	glm::mat4 view, projection;
	// Ptr to GLFW window object
	GLFWwindow* windowptr;

	/// <summary>
	/// Called in ctor. Initializes a GLFW window and sets it as current context
	/// </summary>
	/// <param name="width"> width of window </param>
	/// <param name="height"> height of window </param>
	/// <returns> Pointer to created GLFWWindow</returns>
	GLFWwindow* initGLFWWindowSettings(int width, int height);

	/// <summary>
	/// Makes GLFW aware of callbacks
	/// </summary>
	void initGLFWcallbacks();

public:
	Window();
	~Window();

	/// <summary>
	/// Gets pointer to GLFWWindow
	/// </summary>
	/// <returns> GLFWwindow ptr </returns>
	GLFWwindow* getWindowptr() const;

	// ADD CALLBACKS HERE
	
	/// <summary>
	/// Handles resizing of the window and framebuffer
	/// </summary>
	/// <param name="window"> ptr to window to resize </param>
	/// <param name="width"> width of new window </param>
	/// <param name="height"> height of new window </param>
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	/// <summary>
	/// Handles response to keyboard keys being pressed
	/// </summary>
	/// <param name="window"> ptr to window </param>
	/// <param name="key"> key code </param>
	/// <param name="scancode"> scan code </param>
	/// <param name="action"> status of key pressed </param>
	/// <param name="mods"> modifiers to keyboard (holding down shift) </param>
	static void key_callback(GLFWwindow* window, int key, int scancode, int action,
		int mods);

	/// <summary>
	/// Renders to window
	/// </summary>
	void render();

};
