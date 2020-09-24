#include "SPointLight.h"

namespace {
	using namespace glm;
}

const float SPointLight::MAX_CUTOFF_ANGLE = 180.0f;
const vec3 SPointLight::STANDARD_POS(-3.0f, 0, 3.0f);
const vec3 SPointLight::STANDARD_COL(0.6f, 0.2f, 0.2f);
const vec3 SPointLight::STANDARD_ATTEN(1.0f, 0, 0);
const float SPointLight::STANDARD_CUTOFF = 180.0f;

SPointLight::SPointLight() : position(STANDARD_POS),
                             color(STANDARD_COL),
                             attenuation(STANDARD_ATTEN),
                             cutoff(STANDARD_CUTOFF) {}

void SPointLight::dataToShader(const Shader& program) {
    //TODO
}
