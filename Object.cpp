#include "Object.h"

Object::Object() {
	renderMode = renderType::NORMAL;
}
Object::Object(renderType _renderMode) : renderMode(_renderMode) {}
Object::~Object() {}

void Object::translate(float x, float y, float z) {
	translate(glm::vec3(x, y, z));
}
void Object::translate(glm::vec3 transVec) {
	glm::mat4 translMat(1.0f);
	for (int i = 0; i < 3; ++i) {
		translMat[3][i] += transVec[i];
	}
	model = translMat * model;
}

void Object::rotate(float angle, glm::vec3 axis) {
	glm::mat3 rotMat = glm::rotate(glm::mat4(1.0f), angle, axis);
	glm::mat3 holder = rotMat * glm::mat3(model);
	glm::vec3 transVec = glm::vec3(model[3].x, model[3].y, model[3].z);

	model = glm::mat4(holder);
	model[3].x = transVec.x;
	model[3].y = transVec.y;
	model[3].z = transVec.z;
}

void Object::scale(float sx, float sy, float sz) {
	scale(glm::vec3(sx, sy, sz));
}
void Object::scale(glm::vec3 scaleVec) {
	model = glm::scale(model, scaleVec);
}

void Object::reset() {
	model = glm::mat4(1.0f);
}

void Object::setShaderToRenderType(const Shader& program) const {
	switch (renderMode) {
	case renderType::NORMAL:
		program.setInt("colorMode", 0);
		break;
	case renderType::TEXTURE_WRAP:
		program.setInt("colorMode", 1);
		break;
	case renderType::PHONG:
		program.setInt("colorMode", 2);
		break;
	default:
		std::cout << "Render mode is unrecognized!\n";
		break;
	}
}
