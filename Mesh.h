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
    /// 
    /// </summary>
    /// <param name="vertices"></param>
    /// <param name="indices"></param>
    /// <param name="textures"></param>
    /// <returns></returns>
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
        std::vector<Texture> textures);

    void draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection);
};

