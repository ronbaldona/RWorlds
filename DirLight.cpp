#include "DirLight.h"
#include "PrintDebug.h"

namespace {
	using namespace glm;
}

const vec3 DirLight::STANDARD_COLOR(0, 0.1f, 0.3f);
const vec3 DirLight::STANDARD_DIR(-1.0f, -1.0f, 0);

DirLight::DirLight() : color(STANDARD_COLOR), direction(STANDARD_DIR) {}

void DirLight::dataToShader(const Shader& program) {
	// TODO
	// I KNOW, I KNOW, HARDCODED. I'LL REFACTOR THE CODE LATER ANYWAY. SUE ME
	program.setInt("numDirLights", 1);
	program.setVec3("dLight.color", color);
	program.setVec3("dLight.direction", direction);
}

