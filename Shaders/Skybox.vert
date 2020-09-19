#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 normal;

uniform mat4 view;
uniform mat4 projection;

out vec3 texCoords;

void main() {
   gl_Position = (projection * view * vec4(vertPos, 1.0f)).xyww;
   texCoords = vertPos;
}
