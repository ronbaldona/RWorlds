/* 
     Simple class for rendering ground. Planned to be deleted and replaced later.
	 DEPRECATED
     - RAB
 */
#pragma once

#include "Object.h"
#include "Mesh.h"

class Ground : public Object
{
	// Data
    static const Vertex vertices[4];
    static const glm::ivec3 indices[2];
	
	// Buffer/Array object IDs
    GLuint VAO, VBO, EBO, texID;

	// For tiling the ground
	int numTiles;

	/// <summary>
    /// Loads object from given file
    /// </summary>
    /// <param name="path"> File path name of object </param>
    /// <returns> True if successful, Otherwise false </returns>
    bool load(const char* path);

public:
	Ground();
	~Ground();

	/// <summary>
    /// Draws object to screen.
    /// </summary>
    /// <param name="shaderProg"> ID of shader program to use </param>
    /// <param name="view"> inverse camera transformation matrix </param>
    /// <param name="projection"> projection transformation matrix </param>
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

	/// <summary>
    /// Should send material info to shader...but since ground is deprecated
    /// I won't bother. 
    /// </summary>
    /// <param name="program"></param>
	void sendMatToShader(const Shader& program) const {}
};

