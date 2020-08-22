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
    void draw(GLuint shaderProg, glm::mat4 view, glm::mat4 projection);
};

