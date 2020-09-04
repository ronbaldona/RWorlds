/*
    3D bounding box around each 3D object. Limited to one instantiation so as
    to save resources

    - RAB
 */

// TODO: LOOK INTO SINGLETON CLASSES. CAN THIS BE A SINGLETON?
#pragma once

#include "Object.h"

class BoundingBox3D : public Object
{
    // Show bounding box? Toggleable based on debug mode
    bool showBox;
    
    // TODO: Add members for drawing bounding boxes here

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

};

