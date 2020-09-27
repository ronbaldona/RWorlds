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

uniform mat4 view; // view matrix

uniform int colorMode;    // Color mode (really this is rendering mode)
uniform sampler2D texImg; // 2D texture sampler

uniform int numDirLights;    // number of directional lights
uniform DirLight dLight;     // test directional light
uniform int numSPointLights; // number of spotlights and point lights
uniform SPointLight sPLight; // test point light/spotlight

in vec4 color;  // For normal-based coloring
in vec2 tcoord; // Interpolated texture coordinate
in vec3 normalView; // Normal in view space
in vec3 fragPos; // Fragment position in view space

out vec4 fragColor; // Color of the fragment

/* Calculates single bounce lambertian brdf
 * PARAMETERS:
 *   normal:   Normal in view space
 *   diffuse:  Material diffuse color
 *   lightDir: Normalized light direction from fragPos to light in view space
 *   lightCol: Color of the light
 * RETURNS:
 *   lambertian 3-color after a single bounce
 */
vec3 lambert(vec3 normal, vec3 diffuse, vec3 lightDir, vec3 lightCol) {
    return max(dot(normal, lightDir), 0) * diffuse * lightCol;
}

/* Calculates specular component of the Phong shading model
 * PARAMETERS:
 *   normal:    Normal in view space
 *   specular:  Material specular color
 *   shininess: Shininess power that changes size of specular lobe
 *   lightDir:  Normalized light direction from fragPos to light in view space
 *   lightCol:  Color output of light
 * RETURNS:
 *   Phong specular color
 */
vec3 specular(vec3 normal, vec3 specular, float shininess, vec3 lightDir,
              vec3 lightCol) {
    vec3 viewDir = normalize(fragPos);
    vec3 reflectDir = normalize(reflect(lightDir, normal));
    float specScale = pow(max(dot(viewDir, reflectDir), 0), shininess);
    return specScale * specular * lightCol;
}

void main() {
    vec3 workingCol = vec3(0);
    switch (colorMode) {
    case COLOR_MODE_NORMAL:
        fragColor = color;
        break;
    case COLOR_MODE_TEXTURE_WRAP:
        fragColor = texture(texImg, tcoord);
        break;
    case COLOR_MODE_PHONG:
        for (int i = 0; i < numDirLights; ++i) {
            vec3 lightDir = -normalize(vec3(view * vec4(dLight.direction, 0)));
            workingCol += lambert(normalView, material.diffuse, lightDir, 
                                  dLight.color);
            workingCol += specular(normalView, material.specular, 
                                   material.shininess, lightDir,
                                   dLight.color);
        }
        for (int i = 0; i < numSPointLights; ++i) {
            vec3 lightPosView = vec3(view * vec4(sPLight.position, 1.0f));
            vec3 lightDir = normalize(lightPosView - fragPos);
            workingCol += lambert(normalView, material.diffuse, lightDir,
                                  sPLight.color);
            workingCol += specular(normalView, material.specular,
                                   material.shininess, lightDir,
                                   sPLight.color);
        }
        workingCol += material.ambient;
        fragColor = vec4(workingCol, 1.0f);
        break;
    }
}