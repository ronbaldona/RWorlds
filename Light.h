/*  Purely abstract class for dealing with multiple versions of light casters
    - RAB
 */
#pragma once

#include <glad/glad.h>

#include "Shader.h"
#include "PrintDebug.h"

class Light
{
    // For shadow mapping
    GLuint depthMapFBO, depthMapID;
    const int DEPTH_MAP_SIZE = 1024;


public:
    /// <summary>
    /// Default ctor. Calls set up for depth map
    /// </summary>
    /// <returns></returns>
    Light();
    virtual ~Light();

    /// <summary>
    /// Sends light data to passed in shader program
    /// </summary>
    /// <param name="program"> Shader program being passed in </param>
    virtual void dataToShader(const Shader& program) = 0;

    /// <summary>
    /// Gets the matrix that transforms vertices from world space to NDCs in light
    /// space
    /// </summary>
    /// <returns> Light space transformation matrix to NDCs </returns>
    virtual glm::mat4 getLightSpaceMatrix() const = 0;

    /// <summary>
    /// Sets up depth map texture and framebuffer
    /// </summary>
    void setUpDepthMap();

    /// <summary>
    /// Readies depth map framebuffer for rendering to. Add draw calls after
    /// this function
    /// </summary>
    void startRenderToDepthMap() const;

    /// <summary>
    /// Detaches depth map FBO and resets everything for drawing to screen
    /// </summary>
    /// <param name="windowWidth"> Width of main window </param>
    /// <param name="windowHeight"> Height of main window </param>
    void endRenderToDepthMap(int windowWidth, int windowHeight) const;

    /// <summary>
    /// Binds depth map texture. This is to avoid directly working with the ID
    /// </summary>
    inline void bindDepthMapTexture() {
        glBindTexture(GL_TEXTURE_2D, depthMapID);
    }
};

