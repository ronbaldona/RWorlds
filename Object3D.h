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
	void draw(GLuint shaderProg, glm::mat4 view, glm::mat4 projection);

};
