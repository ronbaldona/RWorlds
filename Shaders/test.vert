#version 330 core

#define COLOR_MODE_NORMAL 0
#define COLOR_MODE_TEXTURE_WRAP 1
#define COLOR_MODE_PHONG 2

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

// Matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 invTransModelview;
uniform mat4 lightTransform;

// Render mode
uniform int colorMode;

// Number of tiles
uniform int numTiles;

// Normal color
out vec4 color;
// Texture coordinate
out vec2 tcoord;
// Normal in view space
out vec3 normalView;
// Position of fragment in view space
out vec3 fragPos;
// Position of fragment in light space NDCs
out vec4 fragPosLightSpace;

void main() {
   gl_Position = projection * view * model * vec4(vertPos, 1.0f);

   if (colorMode == COLOR_MODE_NORMAL)
       color = vec4(0.5f * normal + 0.5f, 1.0f);
   else if (colorMode == COLOR_MODE_TEXTURE_WRAP) {
       tcoord = texCoord;
       tcoord *= numTiles;
       normalView = normalize(vec3(invTransModelview * vec4(0, 1.0f, 0, 0)));
   }
   else if (colorMode == COLOR_MODE_PHONG) {
       normalView = normalize(vec3(invTransModelview * vec4(normal, 0)));
   }
   fragPos = vec3(view * model * vec4(vertPos, 1.0f));
   fragPosLightSpace = lightTransform * model * vec4(vertPos, 1.0f);
}

