#include "DirLight.h"
#include "PrintDebug.h"

namespace {
	using namespace glm;
}

const vec3 DirLight::STANDARD_COLOR(0.4, 0.9f, 0.6f);
const vec3 DirLight::STANDARD_DIR(-1.0f, -1.0f, 0);

DirLight::DirLight() : color(STANDARD_COLOR), direction(STANDARD_DIR) {}

void DirLight::dataToShader(const Shader& program) {
	// TODO
	// I KNOW, I KNOW, HARDCODED. I'LL REFACTOR THE CODE LATER ANYWAY. SUE ME
	program.setInt("numDirLights", 1);
	program.setVec3("dLight.color", color);
	program.setVec3("dLight.direction", direction);
}


glm::mat4 DirLight::getLightSpaceMatrix() const {
	glm::mat4 lightProjMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,
		                                0.5f, 50.0f);
	glm::mat4 lightView = glm::lookAt(glm::vec3(5, 5, 0),
		                              glm::vec3(0),
		                              glm::vec3(0, 1, 0));
	return lightProjMat * lightView;
}
