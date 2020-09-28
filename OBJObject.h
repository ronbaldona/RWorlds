/*
    Simple test class for loading OBJ files. DEPRECATED.
	If a self-written class is what I want, I would write it in a more
	generalized format
	- RAB
 */
#pragma once

#include <glad/glad.h>
#include <vector>

#include "Object.h"

class OBJObject : public Object
{
    // Basic 3D object mesh information
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> indices;

    // TO BE ADDED LATER IF APPROPRIATE
    //std::vector<glm::vec2> texCoords;

    /// <summary>
    /// Helper function that parses the OBJ file
    /// </summary>
    /// <param name="path"> file path name of the OBJ file </param>
    /// <returns> True if successful, False if otherwise </returns>
    bool load(const char* path);

public:
    // Add vertex array objects
    GLuint VAO, EBO;
    GLuint VBOs[2];

    ~OBJObject();

    /// <summary>
    /// ctor that creates a 3D object from a wavefront OBJ file
    /// </summary>
    /// <param name="path"> path to the OBJ file </param>
    /// <returns> N/A </returns>
    OBJObject(const char* path);

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

	/// <summary>
	/// Should send material info to shader...but since OBJObject is deprecated
	/// I won't bother. 
	/// </summary>
	/// <param name="program"></param>
	void sendMatToShader(const Shader& program) const {}

    /// <summary>
	/// Draws object to screen.
	/// </summary>
	/// <param name="shaderProg"> ID of shader program to use </param>
	/// <param name="view"> inverse camera transformation matrix </param>
	/// <param name="projection"> projection transformation matrix </param>
    void draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection);

};

