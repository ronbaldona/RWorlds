#include "Shader.h"

Shader::Shader() {
	// TODO
	ID = 0;
}

Shader::~Shader() {
	glDeleteProgram(ID);
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
	}

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
	}

	// Flag the shaders for deletion. They will be deleted once they are 
	// detached from the program (done also by glDeleteProgram)
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

void Shader::setBool(const std::string& name, bool value) const {
	// TODO
}

void Shader::setInt(const std::string& name, int value) const {
	// TODO
}

void Shader::setFloat(const std::string& name, float value) const {
	// TODO
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	// TODO
}

void Shader::setVec4(const std::string& name, glm::vec4 value) const {
	// TODO
}

void Shader::setMat3(const std::string& name, glm::mat3 value) const {
	// TODO
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	// TODO
}

void Shader::use() {
    // TODO
}
