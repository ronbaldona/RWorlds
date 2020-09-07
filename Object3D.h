/*
    Class that defines any 3D drawable objects. Will be expanded to add
	scaling, rotating functionality
	
	- RAB
 */
#pragma once

#include "Object.h"
#include "BoundingBox3D.h"

class Object3D : public virtual Object {
	// Dimensions of the bounding box containing the object
	glm::vec3 dims;

	// Add rotational information?

	// Bounding Box 

	// 3D Object information



public:
	void draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection);

	/// <summary>
	/// Translates the object
	/// </summary>
	/// <param name="x"> value to translate along x-axis </param>
	/// <param name="y"> value to translate along y-axis </param>
	/// <param name="z"> value to translate along z-axis </param>
	void translate(float x, float y, float z);
	/// <summary>
	/// Translates the object
	/// </summary>
	/// <param name="transVec"> translation vals along axis </param>
	void translate(glm::vec3 transVec);

	/// <summary>
	/// Rotate the object
	/// </summary>
	/// <param name="angle"> angle of rotation </param>
	/// <param name="axis"> axis of rotation </param>
	void rotate(float angle, glm::vec3 axis);

	/// <summary>
	/// Scale object
	/// </summary>
	/// <param name="sx"> scale val along x </param>
	/// <param name="sy"> scale val along y </param>
	/// <param name="sz"> scale val along z </param>
	void scale(float sx, float sy, float sz);
	/// <summary>
	/// Scale object
	/// </summary>
	/// <param name="scaleVec"> scale vals along axis </param>
	void scale(glm::vec3 scaleVec);

	/// <summary>
	/// Resets object's transformations
	/// </summary>
	void reset();

};
