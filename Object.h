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

#include "Shader.h"

class Object {
protected:
	// Places object in world space
	glm::mat4 model = glm::mat4(1.0f);

	// Variables for tracking object

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
	virtual void draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection) = 0;

	// ADD UPDATE FUNCTIONS HERE AS NEEDED
	
	/// <summary>
	/// Translates the object
	/// </summary>
	/// <param name="x"> value to translate along x-axis </param>
	/// <param name="y"> value to translate along y-axis </param>
	/// <param name="z"> value to translate along z-axis </param>
	virtual void translate(float x, float y, float z) = 0;
	/// <summary>
	/// Translates the object
	/// </summary>
	/// <param name="transVec"> translation vals along axis </param>
	virtual void translate(glm::vec3 transVec) = 0;
	
	/// <summary>
	/// Rotate the object
	/// </summary>
	/// <param name="angle"> angle of rotation </param>
	/// <param name="axis"> axis of rotation </param>
	virtual void rotate(float angle, glm::vec3 axis) = 0;

	/// <summary>
	/// Scale object
	/// </summary>
	/// <param name="sx"> scale val along x </param>
	/// <param name="sy"> scale val along y </param>
	/// <param name="sz"> scale val along z </param>
	virtual void scale(float sx, float sy, float sz) = 0;
	/// <summary>
	/// Scale object
	/// </summary>
	/// <param name="scaleVec"> scale vals along axis </param>
	virtual void scale(glm::vec3 scaleVec) = 0;

	/// <summary>
	/// Resets object's transformations
	/// </summary>
	virtual void reset() = 0;
};
