/* 
    Class for 
 */
#pragma once

#include <glm/glm.hpp>

#include "Light.h"

class SPointLight : public Light
{
	// Standard values for default ctor
	static const float MAX_CUTOFF_ANGLE;   // 180.0f
	static const glm::vec3 STANDARD_POS;   // -3, 0, 3
	static const glm::vec3 STANDARD_COL;   // 0.6, 0.2, 0.2
	static const glm::vec3 STANDARD_ATTEN; // 1, 0, 0
	static const float STANDARD_CUTOFF;    // 180

	// Defining values for point light
	glm::vec3 position, color, attenuation;
	// Angle between direction of spotlight and cutoff
	float cutoff;

public:
	/// <summary>
	/// Point light def ctor
	/// </summary>
	SPointLight();

	/// <summary>
	/// Sends light data to passed in shader program
	/// </summary>
	/// <param name="program"> Shader program being passed in </param>
	void dataToShader(const Shader& program);
};

