/*
    Base class for all drawable objects. Serves as the interface for rendering any object
	
	- RAB
 */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <vector>

class Object {
protected:
	// Places object in world space
	glm::mat4 model;

	/// <summary>
	/// Loads object from given file
	/// </summary>
	/// <param name="path"> File path name of object </param>
	/// <returns> True if successful, Otherwise false</returns>
	virtual bool load(const char* path) = 0;

public:

	/// <summary>
	/// Draws object to screen.
	/// </summary>
	/// <param name="shaderProg"> ID of shader program to use </param>
	/// <param name="view"> inverse camera transformation matrix </param>
	/// <param name="projection"> projection transformation matrix </param>
	virtual void draw(GLuint shaderProg, glm::mat4 view, glm::mat4 projection) = 0;

	// ADD UPDATE FUNCTIONS HERE AS NEEDED
};
