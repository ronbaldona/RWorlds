#pragma once

#include <string>
#include <memory>
#include <glad/glad.h>

namespace rworlds::renderer::ogl {

class Shader
{

public:

    std::unique_ptr<Shader> genShader(std::string const& vertPath, std::string const& fragPath);

    ~Shader();

    void attach() const;

private:
    GLuint program;

    Shader() = delete;
    Shader(std::string const& vertPath, std::string const& fragPath);

};

}
