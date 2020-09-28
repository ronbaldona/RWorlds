#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {
	// TODO
	ID = 0;
}


Shader::Shader(const char* vertPath, const char* fragPath) {
	// Read the shader code as a string stream
	std::string vertCode;
	std::string fragCode;
	std::ifstream vertFile;
	std::ifstream fragFile;

	// Set exception masks
	vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::cout << "\nReading shader programs: " << vertPath;
	std::cout << " and " << fragPath << std::endl;

	try {
		// Read file
		vertFile.open(vertPath);
		fragFile.open(fragPath);
		// Put file contents to stream
		std::stringstream vertStream, fragStream;
		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();
		// Close file
		vertFile.close();
		fragFile.close();
		// Turn the file to a string
		vertCode = vertStream.str();
		fragCode = fragStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Shader file was not successfully read\n";
	}
	const char* vertShaderCode, * fragShaderCode;
	vertShaderCode = vertCode.c_str();
	fragShaderCode = fragCode.c_str();

	std::cout << "Compiling shaders\n";

	// Now compile the shaders
	unsigned int vertShader, fragShader;
	int success;
	char infoLog[BUFSIZ];

	// Compiling vertex shader
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	// MAKE SURE THE BOTTOM WORKS
	// Assign source code to shader
	glShaderSource(vertShader, 1, &vertShaderCode, nullptr);
	glCompileShader(vertShader);
	// Check for compiler errors
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertShader, BUFSIZ, nullptr, infoLog);
		std::cout << "Vertex shader compilation failed!\n";
	}

	// Compiling fragment shader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	// MAKE SURE BOTTOM WORKS
	glShaderSource(fragShader, 1, &fragShaderCode, nullptr);
	glCompileShader(fragShader);
	// Check for compiler errors
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, BUFSIZ, nullptr, infoLog);
		std::cout << "Fragment shader compilation failed!\n";
		std::cout << infoLog << std::endl;
	}

	std::cout << "Compiling and linking shaders to full program\n";

	// Create full shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
	// Print any linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, BUFSIZ, nullptr, infoLog);
		std::cout << "Shader linking program failed\n";
		std::cout << infoLog << std::endl;
	}
	glValidateProgram(ID);


	std::cout << "Shader ID: " << ID << std::endl;

	// Flag the shaders for deletion. They will be deleted once they are 
	// detached from the program (done also by glDeleteProgram)
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	std::cout << "Shader set up done!\n\n";
}

void Shader::deleteShader() {
	glDeleteProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, glm::vec4 value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat3(const std::string& name, glm::mat3 value) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, 
		glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
		glm::value_ptr(value));
}

void Shader::use() const {
	glUseProgram(ID);
}

void Shader::printShaderProgramInfoLong() const {
	// ID
	std::cout << "Shader ID: " << ID << std::endl;

	int info;
	char infoLog[BUFSIZ];
	glValidateProgram(ID);
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &info);
	if (!info) {
		std::cout << "- Has failed program validation\n";
		glGetProgramInfoLog(ID, BUFSIZ, nullptr, infoLog);
		std::cout << infoLog << std::endl;
	}

	// Is shader flagged for deletion
	glGetProgramiv(ID, GL_DELETE_STATUS, &info);
	if (info)
		std::cout << "- Is flagged for deletion\n";

	// Get number of attached shaders
	glGetProgramiv(ID, GL_ATTACHED_SHADERS, &info);
	std::cout << "- Has " << info << " shaders attached\n";

	// Get number of active attributes
	glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &info);
	std::cout << "- Has " << info << " attributes\n";

	// Get number of active uniforms
	glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &info);
	std::cout << "- Has " << info << " uniforms\n";
}
