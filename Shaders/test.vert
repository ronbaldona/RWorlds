#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;

void main() {
   gl_Position = projection * view * model * vec4(vertPos, 1.0f);
   color = vec4(0.5f * normal + 0.5f, 1.0f);
}

