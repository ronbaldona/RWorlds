/*  Rudimentary debug printing functions and error handling
    - RAB
 */
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
std::ostream& operator<<(std::ostream& os, const glm::vec2& v);

/// <summary>
/// Prints glm vec3 info to output buffer
/// </summary>
/// <param name="os"> output stream </param>
/// <param name="v"> glm vec3 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::vec3& v);

/// <summary>
/// Print glm vec4 info to output buffer
/// </summary>
/// <param name="os"> Prints glm vec4 info to output buffer </param>
/// <param name="v"> glm vec4 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::vec4& v);

/// <summary>
/// Prints ivec3 info to output buffer
/// </summary>
/// <param name="os"> output stream </param>
/// <param name="v"> glm ivec3 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::ivec3& v);

/// <summary>
/// Prints mat3 info to output buffer
/// </summary>
/// <param name="os"> output buffer </param>
/// <param name="m"> glm mat3 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::mat3& m);

/// <summary>
/// Prints mat4 info to output stream
/// </summary>
/// <param name="os"> output stream </param>
/// <param name="m"> glm mat4 </param>
/// <returns> Output stream </returns>
std::ostream& operator<<(std::ostream& os, const glm::mat4& m);


/// <summary>
/// Namespace will contain basic error handling until a more robust
/// implementation is worked on
/// </summary>
namespace errorHandler {
	/// <summary>
	/// Prints results of glError
	/// </summary>
	void printGlError();
}
