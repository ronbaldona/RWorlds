#include "PrintDebug.h"

#include <glad/glad.h>

std::ostream& operator<<(std::ostream& os, const glm::vec2& v) {
	os << v.x << " " << v.y;
	return os;
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

std::ostream& operator<<(std::ostream& os, const glm::vec4& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

std::ostream& operator<<(std::ostream& os, const glm::ivec3& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

std::ostream& operator<<(std::ostream& os, const glm::mat3& m) {
	os << m[0].x << " " << m[0].y << " " << m[0].z << std::endl;
	os << m[1].x << " " << m[1].y << " " << m[1].z << std::endl;
	os << m[2].x << " " << m[2].y << " " << m[2].z;
	return os;
}

std::ostream& operator<<(std::ostream& os, const glm::mat4& m) {
	os << m[0].x << " " << m[0].y << " " << m[0].z << " " << m[0].w <<
		std::endl;
	os << m[1].x << " " << m[1].y << " " << m[1].z << " " << m[1].w <<
		std::endl;
	os << m[2].x << " " << m[2].y << " " << m[2].z << " " << m[2].w <<
		std::endl;
	os << m[3].x << " " << m[3].y << " " << m[3].z << " " << m[3].w;
	return os;
}

void errorHandler::printGlError() {
	int code = glGetError();
	switch (code) {
	case GL_NO_ERROR:
		std::cout << "NO ERROR\n";
		break;
	case GL_INVALID_ENUM:
		std::cout << "Enumeration parameter is not legal\n";
		break;
	case GL_INVALID_VALUE:
		std::cout << "Value parameter is not legal\n";
		break;
	case GL_INVALID_OPERATION:
		std::cout << "State for a command is not legal for its given parameters\n";
		break;
	case 1283:
		std::cout << "GL stack overflow detected\n";
		break;
	case 1284:
		std::cout << "GL stack underflow detected\n";
		break;
	case GL_OUT_OF_MEMORY:
		std::cout << "GL out of memory\n";
		break;
	default:
		std::cout << "Undefined error code: " << code << std::endl;
		break;
	}
}
