#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

/// <summary>
/// Prints vec2 info to output buffer
/// </summary>
/// <param name="os"> output stream </param>
/// <param name="v"> glm vec2 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::vec2& v) {
	os << v.x << " " << v.y;
	return os;
}

/// <summary>
/// Prints glm vec3 info to output buffer
/// </summary>
/// <param name="os"> output stream </param>
/// <param name="v"> glm vec3 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

/// <summary>
/// Print glm vec4 info to output buffer
/// </summary>
/// <param name="os"> Prints glm vec4 info to output buffer </param>
/// <param name="v"> glm vec4 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::vec4& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

/// <summary>
/// Prints ivec3 info to output buffer
/// </summary>
/// <param name="os"> output stream </param>
/// <param name="v"> glm ivec3 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::ivec3& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

/// <summary>
/// Prints mat3 info to output buffer
/// </summary>
/// <param name="os"> output buffer </param>
/// <param name="m"> glm mat3 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::mat3& m) {
	os << m[0].x << " " << m[0].y << " " << m[0].z << std::endl;
	os << m[1].x << " " << m[1].y << " " << m[1].z << std::endl;
	os << m[2].x << " " << m[2].y << " " << m[2].z;
	return os;
}

/// <summary>
/// Prints mat4 info to output stream
/// </summary>
/// <param name="os"> output stream </param>
/// <param name="m"> glm mat4 </param>
/// <returns> Output stream </returns>
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
