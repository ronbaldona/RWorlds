/*
    Loads meshes from 3D object files. For use with the ASSIMP library. Special thanks
    to learnopengl.com and joeeydevries!

    - RAB
 */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>


#include <string>
#include <vector>

/// <summary>
/// Stores per vertex info
/// </summary>
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoords;
};

/// <summary>
/// Stores texture info
/// </summary>
struct Texture {
    unsigned int id;
    std::string type;
};

/// <summary>
/// Stores mesh information for a model
/// </summary>
class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh();
    ~Mesh();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertices"></param>
    /// <param name="indices"></param>
    /// <param name="textures"></param>
    /// <returns></returns>
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, 
        std::vector<Texture> textures);

};

