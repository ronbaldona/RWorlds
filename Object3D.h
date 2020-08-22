/*
    Class that defines any 3D drawable objects
	
	- RAB
 */
#pragma once

#include "Object.h"
#include "BoundingBox3D.h"

class Object3D : public virtual Object {
	// Dimensions of the bounding box containing the object
	glm::vec3 dims;

public:
	void draw(GLuint shaderProg, glm::mat4 view, glm::mat4 projection);

};
