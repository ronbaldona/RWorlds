/*
    Loads meshes from 3D object files. For use with the ASSIMP library. Special thanks
    to learnopengl.com and joeeydevries!

    - RAB
 */
#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader.h"

/// <summary>
/// Stores per vertex info
/// </summary>
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

/// <summary>
/// Stores texture info
/// </summary>
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

/// <summary>
/// Stores mesh information for a model
/// </summary>
class Mesh
{
    friend class Model;
    // Data rendering
    unsigned int VAO, VBO, EBO;

    /// <summary>
    /// Initializes buffer objects for rendering
    /// </summary>
    void init();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    /// <summary>
    /// Mesh constructor. Copies all info from passed vector objects
    /// </summary>
    /// <param name="vertices"> contains position info </param>
    /// <param name="indices"> contains index info </param>
    /// <param name="textures"> contains texture info </param>
    /// <returns> N/A </returns>
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
        std::vector<Texture> textures);

    /// <summary>
    /// Gets AABB corner positions of mesh
    /// </summary>
    /// <param name="minCorner"> Stores min corner </param>
    /// <param name="maxCorner"> Stores max corner </param>
    void getCornerVecs(glm::vec3& minCorner, glm::vec3& maxCorner) const;

    /// <summary>
    /// Updates VBO with vertex data currently stored by model
    /// </summary>
    void updateBuffers() const;

    /// <summary>
    /// DEPRECATED. Draws mesh to screen
    /// </summary>
    /// <param name="shaderProg"> Shader program </param>
    /// <param name="view"> view matrix</param>
    /// <param name="projection"> projection matrix </param>
    void draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection);

    /// <summary>
    /// Draws mesh to screen
    /// </summary>
    /// <param name="shaderProg"> Shader program </param>
    /// <param name="model"> model matrix </param>
    /// <param name="view"> view matrix </param>
    /// <param name="projection"> projection matrix </param>
    void draw(Shader shaderProg,
        glm::mat4& model,
        glm::mat4& view,
        glm::mat4& projection);

};

