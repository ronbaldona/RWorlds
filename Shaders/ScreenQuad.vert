#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texCoords;

out vec2 fragTexCoords;

void main () {
    // Always render the quad to screen
    gl_Position = vec4(vertPos.xy, -1, 1);
	fragTexCoords = 0.5f * vertPos.xy + 0.5f;
}