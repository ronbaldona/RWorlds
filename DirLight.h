/*
   Directional Light implementation
   - RAB
 */
#pragma once

#include <glm/glm.hpp>

#include "Light.h"

class DirLight : public Light {
	// Standard values for default ctor
	static const glm::vec3 STANDARD_COLOR; // 0, 1, 0
	static const glm::vec3 STANDARD_DIR;   // 0, -1, 0

	// Values to be sent to shader
	glm::vec3 color, direction;

public:
	/// <summary>
	/// default ctor
	/// </summary>
	DirLight();
    
	/// <summary>
	/// Sends DirLight data to shader
	/// </summary>
	/// <param name="program"> shader program to send data to </param>
	void dataToShader(const Shader& program);

};

