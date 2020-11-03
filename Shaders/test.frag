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
uniform sampler2D depthMap; // Depth map
uniform sampler2D texImg; // 2D texture sampler

uniform int numDirLights;    // number of directional lights
uniform DirLight dLight;     // test directional light
uniform int numSPointLights; // number of spotlights and point lights
uniform SPointLight sPLight; // test point light/spotlight

in vec4 color;  // For normal-based coloring
in vec2 tcoord; // Interpolated texture coordinate
in vec3 normalView; // Normal in view space
in vec3 fragPos; // Fragment position in view space
in vec4 fragPosLightSpace; // Fragment position in (clip) light space

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
    vec3 viewDir = normalize(-fragPos);
    vec3 halfVec = normalize(viewDir + lightDir);
    //vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float specScale = pow(max(dot(normal, halfVec), 0), shininess);
    return specScale * specular * lightCol;
}

float calcShadowWeight() {
    // Hardcoded values that should be changed if/when i revisit this project
    float bias = 0.001f;
    float texelSize = 1.0f / 1024.0f;

    // Properly transform NDCs to texture coordinates in [0, 1]
    vec3 fragLightNDC = fragPosLightSpace.xyz / fragPosLightSpace.w;
    fragLightNDC = 0.5f * fragLightNDC + 0.5f;
    
    // Depth comparison
    if (fragLightNDC.z > 1.0f)
        return 0;

    // Apply convolution
    float inShadow = 0;
    float numSamples = 0;
    for (int x = -2; x <= 2; ++x) {
        for (int y = -2; y <= 2; ++y) {
           float texDepth = texture(depthMap, 
                                    fragLightNDC.xy + vec2(x, y) * texelSize).r
                            + bias;
           inShadow += (fragLightNDC.z > texDepth) ? 1.0f : 0;
           ++numSamples;
        }
    }
    inShadow /= numSamples;
    //float texDepth = texture(depthMap, fragLightNDC.xy).r + bias;
    //inShadow = (fragLightNDC.z > texDepth) ? 1.0f : 0;

    return inShadow;
}

void main() {
    vec3 workingCol = vec3(0);

    float shadow = calcShadowWeight();
    
    switch (colorMode) {
    case COLOR_MODE_NORMAL:
        workingCol = color.xyz;
        break;
    case COLOR_MODE_TEXTURE_WRAP:
        vec3 texColor = texture(texImg, tcoord).xyz;
        vec3 lightDir = -normalize(vec3(view * vec4(dLight.direction, 0)));

        vec3 ambient = texColor * 0.05f;
        vec3 diffuse = lambert(normalView, texColor, lightDir, dLight.color);
        vec3 spec = specular(normalView, vec3(1), 40.0f, lightDir, dLight.color);
        workingCol = (1.0f - shadow) * (ambient + diffuse + spec);
        //workingCol = (1.0f - shadow) * texture(texImg, tcoord).xyz;
        break;
    case COLOR_MODE_PHONG:
        // Directional lights
        for (int i = 0; i < numDirLights; ++i) {
            vec3 lightDir = -normalize(vec3(view * vec4(dLight.direction, 0)));
            workingCol += lambert(normalView, material.diffuse, lightDir, 
                                  dLight.color);
            workingCol += specular(normalView, material.specular, 
                                   material.shininess, lightDir,
                                   dLight.color);
        }
        // Point lights
        for (int i = 0; i < numSPointLights; ++i) {
            vec3 lightPosView = vec3(view * vec4(sPLight.position, 1.0f));
            vec3 lightDir = normalize(lightPosView - fragPos);
            workingCol += lambert(normalView, material.diffuse, lightDir,
                                  sPLight.color);
            workingCol += specular(normalView, material.specular,
                                   material.shininess, lightDir,
                                   sPLight.color);
        }

        workingCol *= (1.0f - shadow);
        workingCol += material.ambient;
        break;
    }
    
    fragColor = vec4(workingCol, 1.0f);

}