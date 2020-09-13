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
#include "Model.h"
#include "Camera.h"

class Window {
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
	/// ctor that creates a window with a user-specified width and height
	/// </summary>
	/// <param name="width"> Pixel width of window</param>
	/// <param name="height"> Pixel height of window</param>
	/// <returns> N/A </returns>
	Window(int _width, int _height);

	/// <summary>
	/// Gets pointer to GLFWWindow
	/// </summary>
	/// <returns> GLFWwindow ptr </returns>
	GLFWwindow* getWindowptr() const;

	/// <summary>
	/// Temporary function. Used to set obj to view
	/// </summary>
	/// <param name="path"></param>
	static void setObjToView(const std::string& path);

	/// <summary>
	/// Initializes scene (Rendering objects, shader programs, etc)
	/// </summary>
	static void initializeScene();
	
	/// <summary>
	/// Cleans up after anything initializes using initializeScene
	/// </summary>
	static void cleanUpScene();
	
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
	/// Callback function for getting cursor position over window
	/// </summary>
	/// <param name="window"> Pointer to GLFW window </param>
	/// <param name="xpos"> x position of cursor on screen space </param>
	/// <param name="ypos"> y position of cursor on screen space </param>
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	/// <summary>
	/// Callback function for dealing with mouse button presses
	/// </summary>
	/// <param name="window"> Pointer to GLFW window </param>
	/// <param name="button"> ID of mouse button pressed </param>
	/// <param name="action"> Action IDs </param>
	/// <param name="mods">< Modification ID /param>
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	/// <summary>
	/// Callback function for dealing with scrolling
	/// </summary>
	/// <param name="window"> GLFWwindow pointer </param>
	/// <param name="xoffset"> amount of offset in x axis </param>
	/// <param name="yoffset"> amount of offset in y axis </param>
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	/// <summary>
	/// Renders to window
	/// </summary>
	void render();

};
