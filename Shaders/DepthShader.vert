#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

// Matrices
uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
uniform mat4 lightTransform;

void main() {
   gl_Position = lightTransform * model * vec4(vertPos, 1.0f);
}
