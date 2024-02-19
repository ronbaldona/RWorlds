#pragma once

#include <stdexcept>
#include <memory>
#include <array>
#include <glad/glad.h>

#include <Geom/Triangle.h>

namespace rworlds::renderer {

class RenderTri
{
public:

    static std::unique_ptr<RenderTri> genRenderTri(geom::Triangle& tri)
    {
        return std::unique_ptr<RenderTri>(new RenderTri(tri));
    }

    ~RenderTri()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }

    void draw() const
    {
        throw std::runtime_error("RenderTri:draw - Don't forget to attach the shader program!");

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }

   
private:
    static std::array<GLuint, 3> idxs;

    geom::Triangle tri;
    GLuint vao, vbo, ebo;


    RenderTri(geom::Triangle const& _tri)
    {
        tri = _tri;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tri), &tri, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * idxs.size(), idxs.data(), GL_STATIC_DRAW);

        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

};

}
