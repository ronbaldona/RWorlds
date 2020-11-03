/* 
     Simple class for rendering ground. Planned to be deleted and replaced later.
	 DEPRECATED
     - RAB
 */
#pragma once

#include <glad/glad.h>

#include "Object.h"

// Struct is defined at Mesh.h (should move later)
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
    /// <param name="program"> ID of shader program to use </param>
    /// <param name="view"> inverse camera transformation matrix </param>
    /// <param name="projection"> projection transformation matrix </param>
	void draw(const Shader& program, glm::mat4 view, glm::mat4 projection);

	/// <summary>
    /// Should send material info to shader...but since ground is deprecated
    /// I won't bother. 
    /// </summary>
    /// <param name="program"></param>
	void sendMatToShader(const Shader& program) const {}
};

