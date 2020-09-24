#include "Ground.h"
#include "stb_image.h"

const Vertex Ground::vertices[4] = {
	// ll
	{glm::vec3(-100, -3, 100), glm::vec3(0, 1, 0), glm::ivec2(0, 0)},
	// lr
	{glm::vec3(100, -3, 100), glm::vec3(0, 1, 0), glm::ivec2(1, 0)},
	// ul
	{glm::vec3(-100, -3, -100), glm::vec3(0, 1, 0), glm::ivec2(0, 1)},
	// ur
	{glm::vec3(100, -3, -100), glm::vec3(0, 1, 0), glm::ivec2(1, 1)}
};
const glm::ivec3 Ground::indices[2] = {
	glm::ivec3(0, 1, 3),
	glm::ivec3(3, 2, 0)
};

Ground::Ground() : Object(renderType::TEXTURE_WRAP) {
	load("Models/ground_metal.jpg");

	numTiles = 50;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(glm::ivec3), indices, 
		         GL_STATIC_DRAW);

	// Tell OpenGL how to read data
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                  (void*)offsetof(Vertex, normal));
	// Texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                  (void*)offsetof(Vertex, texCoords));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Ground::~Ground() {
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &texID);
}

bool Ground::load(const char* path) {
	int width, height, nrChannels;
	unsigned char* data;
	if (!(data = stbi_load(path, &width, &height, &nrChannels, 0))) {
		std::cout << "Texture at path: " << path << " failed to load!\n";
		stbi_image_free(data);
		return false;
	}

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, 
		         GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return true;
}

void Ground::translate(float x, float y, float z) {
	translate(glm::vec3(x, y, z));
}
void Ground::translate(glm::vec3 transVec) {
	glm::mat4 translMat(1.0f);
	for (int i = 0; i < 3; ++i) {
		translMat[3][i] += transVec[i];
	}
	model = translMat * model;
}

void Ground::rotate(float angle, glm::vec3 axis) {
	glm::mat3 rotMat = glm::rotate(glm::mat4(1.0f), angle, axis);
	glm::mat3 holder = rotMat * glm::mat3(model);
	glm::vec3 transVec = glm::vec3(model[3].x, model[3].y, model[3].z);

	model = glm::mat4(holder);
	model[3].x = transVec.x;
	model[3].y = transVec.y;
	model[3].z = transVec.z;
}

void Ground::scale(float sx, float sy, float sz) {
	scale(glm::vec3(sx, sy, sz));
}
void Ground::scale(glm::vec3 scaleVec) {
	model = glm::scale(model, scaleVec);
}

void Ground::reset() {
	model = glm::mat4(1.0f);
}

void Ground::draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection) {
	shaderProg.use();
	setShaderToRenderType(shaderProg);
	shaderProg.setInt("numTiles", numTiles);
	shaderProg.setMat4("model", model);
	shaderProg.setMat4("view", view);
	shaderProg.setMat4("projection", projection);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
