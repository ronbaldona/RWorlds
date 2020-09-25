/*
    Base class for all drawable objects. Serves as the interface for rendering any object
	Will rewrite
	
	- RAB
 */
#pragma once

#include <vector>

#include "Shader.h"

enum class renderType
{
	NORMAL,
	TEXTURE_WRAP,
	PHONG
};

class Object {
protected:
	// Places object in world space
	glm::mat4 model = glm::mat4(1.0f);
	
	// Mode for object to be rendered in 
	renderType renderMode = renderType::NORMAL;

	/// <summary>
	/// Loads object from given file
	/// </summary>
	/// <param name="path"> File path name of object </param>
	/// <returns> True if successful, Otherwise false </returns>
	virtual bool load(const char* path) = 0;

public:
	/// <summary>
	/// Base constructor that sets rendering mode to normal coloring
	/// </summary>
	Object() { renderMode = renderType::NORMAL; }
	/// <summary>
	/// Base constructor that sets rendering mode to parameter
	/// </summary>
	/// <param name="_renderMode"> type of rendering mode to set </param>
	Object(renderType _renderMode) : renderMode(_renderMode) {}
	
	/// <summary>
	/// Draws object to screen.
	/// </summary>
	/// <param name="shaderProg"> ID of shader program to use </param>
	/// <param name="view"> inverse camera transformation matrix </param>
	/// <param name="projection"> projection transformation matrix </param>
	virtual void draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection) = 0;

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

	/// <summary>
	/// Gets the rendering mode for the given 3D object
	/// </summary>
	/// <returns> enum that describes what render mode object is </returns>
	renderType getRenderMode() const { return renderMode; }
	/// <summary>
	/// Sets rendering mode for given 3D object
	/// </summary>
	/// <param name="renderMode"> Sets the given rendering mode to parameter </param>
	void setRenderMode(renderType renderMode) { this->renderMode = renderMode; }
	/// <summary>
	/// Sets render mode in shader program
	/// </summary>
	/// <param name="program"> program to set render mode in </param>
	void setShaderToRenderType(const Shader& program) const {
		switch (renderMode) {
		case renderType::NORMAL:
			program.setInt("colorMode", 0);
			break;
		case renderType::TEXTURE_WRAP:
			program.setInt("colorMode", 1);
			break;
		case renderType::PHONG:
			program.setInt("colorMode", 2);
			break;
		default:
			std::cout << "Render mode is unrecognized!\n";
			break;
		}
	}

	/// <summary>
	/// Sends material value to shader of interest
	/// </summary>
	/// <param name="program"> Shader program to send vals to </param>
	virtual void sendMatToShader(const Shader& program) const = 0;

};
