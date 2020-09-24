#include "DirLight.h"

namespace {
	using namespace glm;
}

const vec3 DirLight::STANDARD_COLOR(0, 1.0f, 0);
const vec3 DirLight::STANDARD_DIR(0, -1.0f, 0);

DirLight::DirLight() : color(STANDARD_COLOR), direction(STANDARD_DIR) {}

void DirLight::dataToShader(const Shader& program) {
	// TODO
}
