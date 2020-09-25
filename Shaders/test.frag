#version 330 core

#define COLOR_MODE_NORMAL 0
#define COLOR_MODE_TEXTURE_WRAP 1
#define COLOR_MODE_PHONG 2

// Defines data needed for directional light
struct DirLight {
    vec3 color, direction;
};

// Defines data needed for spotlight/point light
struct SPointLight {
    vec3 position, color, attenuation;
    float cutoff;
};

struct Material {
    vec3 ambient, diffuse, specular;
    float shininess;
};
uniform Material material;

uniform int colorMode;    // Color mode (really this is rendering mode)
uniform sampler2D texImg; // 2D texture sampler

uniform int numDirLights;    // number of directional lights
uniform DirLight dLight;     // test directional light
uniform int numSPointLights; // number of spotlights and point lights
uniform SPointLight sPLight; // test point light/spotlight


in vec4 color;  // For normal-based coloring
in vec2 tcoord; // Interpolated texture coordinate

out vec4 fragColor; // Color of the fragment
void main() {
    switch (colorMode) {
    case COLOR_MODE_NORMAL:
        fragColor = color;
        break;
    case COLOR_MODE_TEXTURE_WRAP:
        fragColor = texture(texImg, tcoord);
        break;
    case COLOR_MODE_PHONG:
        /*
        */
        break;
    }
}