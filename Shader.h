/*
    Handles loading and using any OpenGL shader programs

	- RAB
 */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	// Identifies shader
	unsigned int ID;

public:
	Shader();
	~Shader();

	// Add more shader constructors HERE
	
	/// <summary>
	/// ctor builds an OpenGL shader
	/// </summary>
	/// <param name="vertPath"> File path to the vertex shader </param>
	/// <param name="fragPath"> File path to the fragment shader </param>
	/// <returns> N/A </returns>
	Shader(const char* vertPath, const char* fragPath);
	
	// Uniform setter functions
	/// <summary>
	/// Sets bool uniform in shader program
	/// </summary>
	/// <param name="name"> Name of variable to set </param>
	/// <param name="value">  Value of variable to set </param>
	void setBool(const std::string& name, bool value) const;
	// Same as above but with ints
	void setInt(const std::string& name, int value) const;
	// Same as above but with floats
	void setFloat(const std::string& name, float value) const;
	// Same as above but with glm::vec3
	void setVec3(const std::string& name, glm::vec3 value) const;
	// Same as above but with glm::vec4
	void setVec4(const std::string& name, glm::vec4 value) const;
	// Same as above but with glm::mat3
	void setMat3(const std::string& name, glm::mat3 value) const;
	// Same as above but with glm::mat4
	void setMat4(const std::string& name, glm::mat4 value) const;

	/// <summary>
    /// Tell OpenGL to use this shader
    /// </summary>
    /// <returns> N/A </returns>
	void use();
};

