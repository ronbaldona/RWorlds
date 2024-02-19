#include "Renderer/OpenGL/Shader.h"

#include <stdexcept>

namespace rworlds::renderer::ogl {

std::unique_ptr<Shader> Shader::genShader(std::string const& vertPath, std::string const& fragPath)
{
    return std::unique_ptr<Shader>(new Shader(vertPath, fragPath));
}

Shader::Shader(std::string const& vertPath, std::string const& fragPath) :
    program(glCreateProgram())
{
    throw std::runtime_error("ogl::shader ctor - did not implement this yet");

    // Load vert string using filesystem load
    // Compile shader
    // check for success

    // Load frag string using filesystem load
    // Compile shader
    // check for success

    // link shaders
    // check for success

    // delete shaders
}

Shader::~Shader()
{
    glDeleteProgram(program);
}


void Shader::attach() const
{

}

}
