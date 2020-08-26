/*
    Simple test clasa for loading OBJ files
 */
#pragma once

#include "Object.h"

class OBJObject : public Object
{
    // Basic 3D object mesh information
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> indices;

    // TO BE ADDED LATER IF APPROPRIATE
    //std::vector<glm::vec2> texCoords;

    // Add vertex array objects
    GLuint VAO, VBOs[2], EBO;

    /// <summary>
    /// Helper function that parses the OBJ file
    /// </summary>
    /// <param name="path"> file path name of the OBJ file </param>
    /// <returns> True if successful, False if otherwise </returns>
    bool load(const char* path);

public:
    ~OBJObject();

    /// <summary>
    /// ctor that creates a 3D object from a wavefront OBJ file
    /// </summary>
    /// <param name="path"> path to the OBJ file </param>
    /// <returns> N/A </returns>
    OBJObject(const char* path);

    /// <summary>
	/// Draws object to screen.
	/// </summary>
	/// <param name="shaderProg"> ID of shader program to use </param>
	/// <param name="view"> inverse camera transformation matrix </param>
	/// <param name="projection"> projection transformation matrix </param>
    void draw(GLuint shaderProg, glm::mat4 view, glm::mat4 projection);

};

