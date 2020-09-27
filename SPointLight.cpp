#include "SPointLight.h"

namespace {
	using namespace glm;
}

const float SPointLight::MAX_CUTOFF_ANGLE = 180.0f;
const vec3 SPointLight::STANDARD_POS(-1.0f, 0, 2.0f);
const vec3 SPointLight::STANDARD_COL(0.4);
const vec3 SPointLight::STANDARD_ATTEN(1.0f, 0, 0);
const float SPointLight::STANDARD_CUTOFF = 180.0f;

SPointLight::SPointLight() : position(STANDARD_POS),
                             color(STANDARD_COL),
                             attenuation(STANDARD_ATTEN),
                             cutoff(STANDARD_CUTOFF) {}

void SPointLight::dataToShader(const Shader& program) {
    // TODO
    // I KNOW, I KNOW, HARDCODED. I'LL REFACTOR THE CODE LATER ANYWAY. SUE ME
    program.setInt("numSPointLights", 1);

    program.setVec3("sPLight.position", position);
    program.setVec3("sPLight.color", color);
    program.setVec3("sPLight.attenuation", attenuation);
    program.setFloat("sPLight.cutoff", cutoff);
}
