#include "Skybox.h"

#include "PrintDebug.h"

const glm::vec3 Skybox::vertices[8] = {
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f)
};

const glm::ivec3 Skybox::indices[12] = {
	// Front face
	glm::ivec3(0, 4, 5),
	glm::ivec3(0, 5, 1),
	// Back face
	glm::ivec3(2, 7, 6),
	glm::ivec3(2, 3, 7),
	// Left face
	glm::ivec3(0, 6, 4),
	glm::ivec3(0, 2, 6),
	// Right face
	glm::ivec3(1, 5, 7),
	glm::ivec3(1, 7, 3),
	// Top face
	glm::ivec3(4, 6, 7),
	glm::ivec3(4, 7, 5),
	// Bottom face
	glm::ivec3(0, 3, 2),
	glm::ivec3(0, 1, 3)
};

Skybox::Skybox() {
	loadCubemap("Skybox/Default");
	init();
}

Skybox::Skybox(const char* path) {
	loadCubemap(path);
	init();
}

Skybox::~Skybox() {
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &texId);
}

/// <summary>
/// 
/// </summary>
/// <param name="filePathArray"></param>
/// <param name="counterArray"></param>
/// <param name="filepath"></param>
/// <param name="ind"></param>
void setCubemapStringArray(std::string* filePathArray,
	int* counterArray,
	const std::string& filepath,
	int ind) {

	if (filePathArray == nullptr || counterArray == nullptr) {
		std::cout << "In setCubemapStringArray: SENT INVALID PTR AS PARAMETERS\n";
		std::cout << "Exiting\n";
		exit(EXIT_FAILURE);
	}
	if (ind < 0 || ind >= 6) {
		std::cout << "In setCubeMapStringArray: Ind range should be 0-5\n";
		return;
	}

	if (++counterArray[ind] != 1) {
		std::cout << "Replacing " << filePathArray[ind] << " " << "with ";
		std::cout << filepath << std::endl;
	}
	filePathArray[ind] = filepath;
}

bool Skybox::loadCubemap(const char* path) {
	std::cout << "Loading cubemap textures from " << path << std::endl;

	// Get directory name
	std::string dirName = std::string(path);
	if (dirName[dirName.length() - 1] == '/')
		dirName = dirName.substr(0, dirName.find_last_of('/') - 1);

	// Get names of each cubemap texture
	const int NUM_FACES = 6;
	int faceCounter[NUM_FACES] = { 0, 0, 0, 0, 0, 0 };
	std::string fileNames[NUM_FACES];
	for (auto& file : std::filesystem::directory_iterator(dirName)) {
		std::string currName = file.path().string();

		// Parse out which face of skybox the img is for
		std::replace(currName.begin(), currName.end(), '\\', '/');
		std::string type = currName.substr(currName.find_last_of('_') + 1, 1);

		// Place it in array of file strings. Keep track of filenames
		switch (type[0]) {
		case 'u':
			setCubemapStringArray(fileNames, faceCounter, currName, POSITIVE_Y);
			break;
		case 'd':
			setCubemapStringArray(fileNames, faceCounter, currName, NEGATIVE_Y);
			break;
		case 'l':
			setCubemapStringArray(fileNames, faceCounter, currName, NEGATIVE_X);
			break;
		case 'r':
			setCubemapStringArray(fileNames, faceCounter, currName, POSITIVE_X);
			break;
		case 'f':
			setCubemapStringArray(fileNames, faceCounter, currName, NEGATIVE_Z);
			break;
		case 'b':
			setCubemapStringArray(fileNames, faceCounter, currName, POSITIVE_Z);
			break;
		default:
			std::cout << "Skybox type not recognized!\n";
			std::cout << "Ignoring " << currName << std::endl;
		}
	}

	// Check if we loaded all string names correctly
	for (unsigned int i = 0; i < NUM_FACES; ++i) {
		if (!faceCounter[i]) {
			std::cout << "Missing a texture for a cubemap in " << path << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	// Create textures
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

	int width, height, nrChannels;
	unsigned char* data;
	for (unsigned int i = 0; i < NUM_FACES; ++i) {
		// TODO
		data = stbi_load(fileNames[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
			std::cout << "Failed to load data!\n";

		// Free image memory
		stbi_image_free(data);
	}

	// Texture sampler settings
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return true;
}

void Skybox::init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO to modify it
	glBindVertexArray(VAO);

	// Bind VBO to attach to VAO as an array buffer. This will modify it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Add data to VBO
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), vertices,
		GL_STATIC_DRAW);
	// Specify location of VBO data by enabling layout location 0
	glEnableVertexAttribArray(0);
	// Set metadata that specifies how OpenGL will walk through each vertex
	glVertexAttribPointer(
		0,  // Starts at layout location 0
		3,  // 3 components per vertex
		GL_FLOAT,  // of type GL_FLOAT
		GL_FALSE,  // Do not normalize data
		3 * sizeof(GL_FLOAT),  // Offset between consecutive vertices
		(GLvoid*)0  // Offset of the 1st vertex component
	);

	// Add element array buffer for dealing with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(glm::ivec3),
		indices, GL_STATIC_DRAW);

	// Unbind GL_ARRAY_BUFFER (DO NOT UNBIND ELEMENT ARRAY BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Skybox::draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection) {
	glDepthFunc(GL_LEQUAL);
	shaderProg.use();
	glm::mat4 newView = glm::mat4(glm::mat3(view));
	shaderProg.setMat4("view", newView);
	shaderProg.setMat4("projection", projection);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}
