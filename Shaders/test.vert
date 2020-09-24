#version 330 core

#define COLOR_MODE_NORMAL 0
#define COLOR_MODE_TEXTURE_WRAP 1

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int colorMode;

uniform int numTiles;

out vec4 color;
out vec2 tcoord;

void main() {
   gl_Position = projection * view * model * vec4(vertPos, 1.0f);
   color = vec4(0.5f * normal + 0.5f, 1.0f);
   tcoord = texCoord;
   if (colorMode == COLOR_MODE_TEXTURE_WRAP) {
       tcoord *= numTiles;
   }
}

