#include "OBJObject.h"

#include <iostream>

namespace {
	const int VEC_3_NUM_COMPONENTS = 3;
	const int FACE_MAX_NUM_COMPONENTS = 6;
}


OBJObject::~OBJObject() {
	glDeleteBuffers(2, VBOs);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

}

OBJObject::OBJObject(const char* path) : Object() {
	model = glm::mat4(1.0f);
	// Load OBJ file info
	load(path);

	// Prepare object information to send to GPU
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBOs);
	glGenBuffers(1, &EBO);

	// Bind VAO to modify it
	glBindVertexArray(VAO);

	// Bind VBO to attach to VAO as an array buffer. This will modify it
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	// Add data to VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), 
		vertices.data(), GL_STATIC_DRAW);
	// Specify location of VBO data by enabling layout location 0
	glEnableVertexAttribArray(0);
	// Set metadata that specifies how OpenGL will walk through each vertex
	glVertexAttribPointer(0,  // Starts at layout location 0
		3,  // 3 components per vertex
		GL_FLOAT,  // of type GL_FLOAT
		GL_FALSE,  // Do not normalize data
		3 * sizeof(GL_FLOAT),  // Offset between consecutive vertices
		(GLvoid*)0  // Offset of the 1st vertex component
	);

	// Move to dealing with normal data
	// Bind VBO to attach to VAO as an array buffer. This will modify it
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	// Add data to VBO
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
		normals.data(), GL_STATIC_DRAW);
	// Specify location of VBO data by enabling layout location 1
	glEnableVertexAttribArray(1);
	// Set metadata that specifies how OpenGL will walk through each vertex
	glVertexAttribPointer(1,  // Starts at layout location 1
		3,  // 3 components per vertex
		GL_FLOAT,  // of type GL_FLOAT
		GL_TRUE,  // Do not normalize data
		3 * sizeof(GL_FLOAT),  // Offset between consecutive vertices
		(GLvoid*)0  // Offset of the 1st vertex component
	);
	
	// Add element array buffer for dealing with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::ivec3),
		indices.data(), GL_STATIC_DRAW);

	// Unbind GL_ARRAY_BUFFER (DO NOT UNBIND ELEMENT ARRAY BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool OBJObject::load(const char* path) {
	FILE* fp;
	glm::vec3 vertex, normal;
	glm::ivec3 index;
	int c1, c2, result;

	std::vector<glm::vec3> vertexHolder, normalHolder;
	std::vector<glm::ivec3> indexHolder;

	// Read file
	std::cout << "Reading file from " << path << std::endl;
	fopen_s(&fp, path, "rb");
	if (fp == nullptr) {
		std::cout << "Failed to read file!\n Exiting program...\n";
		exit(EXIT_FAILURE);
	}

	// Read from file
	result = 0;
	while ((c1 = fgetc(fp)) != EOF) {
		// Comment lines
		if (c1 == '#') {
			// Move to next line, ignoring current read line
			// REPLACE IF DOES NOT WORK
			// Read all lines except newline, then read newline, don't put it to 
			// any variable
			fscanf_s(fp, "%*[^\n]%*c");
			continue;
		}

		c2 = fgetc(fp);
		// Vertex position
		if (c1 == 'v' && c2 == ' ') {
			// Read vertex information (ignores color info)
			result = fscanf_s(fp, "%f %f %f %*f %*f %*f\r\n",
				&vertex.x, &vertex.y, &vertex.z);

			if (result != VEC_3_NUM_COMPONENTS) {
				std::cout << "Parsing OBJ failure on v\n";
				exit(EXIT_FAILURE);
			}

			//vertexHolder.push_back(glm::vec3(vertex));
			vertices.push_back(glm::vec3(vertex));
		}
		// Vertex normal
		else if (c1 == 'v' && c2 == 'n') {
			result = fscanf_s(fp, "%f %f %f\r\n",
				&normal.x, &normal.y, &normal.z);
			//normalHolder.push_back(vertex);
			normals.push_back(normalize(normal));

			if (result != VEC_3_NUM_COMPONENTS) {
				std::cout << "Parsing OBJ failure on vn\n";
				exit(EXIT_FAILURE);
			}
		}
		// Vertex textures
		else if (c1 == 'v' && c2 == 't') {
			// TODO
		}

		// Parameter space vertices


		// Face indices
		else if (c1 == 'f' && c2 == ' ') {
			result = fscanf_s(fp, "%d//%*d %d//%*d %d//%*d\r\n",
				&index.x, &index.y, &index.z);
			
			/*
			// face also includes texture data but no normal data
			if (result == 1) {
				result = fscanf_s(fp, "%*d %d/%*d %d/%*d\r\n",
					&index.y, &index.z);

				// face also includes normal data
				if (!result) {
					result = fscanf_s(fp, "/%*d %d/%*d/%*d %d/%*d/%*d\r\n",
						&index.y, &index.z);

					if (result != 2) {
						std::cout << "Parsing OBJ failure on f\r\n";
						exit(EXIT_FAILURE);
					}
				}

				// Replace magic number later?
				else if (result != 2) {
					std::cout << "Parsing OBJ failure on f\r\n";
					exit(EXIT_FAILURE);
				}
			}
			*/

			// Failed to parse face index data
			//else if (result != 3) {
			if (result != 3) {
				std::cout << "Failed to parse face index data\r\n";
				exit(EXIT_FAILURE);
			}
			indices.push_back(index - glm::ivec3(1));
		}
	}

	std::cout << "Number of vertices: " << vertices.size() << std::endl;
	std::cout << "Number of vertex normals: " << normals.size();
	std::cout << std::endl;
	//std::cout << "Number of faces: " << indexHolder.size() << std::endl;
	std::cout << "Number of faces: " << indices.size() << std::endl;

	// Sort vertices by order of indices
	/*
	glm::ivec3 currIndexVec = glm::ivec3(0, 1, 2);
	for (auto triIndex : indexHolder) {
		for (int i = 0; i < VEC_3_NUM_COMPONENTS; ++i) {
			vertices.push_back(vertexHolder[triIndex[i]]);
			normals.push_back(normalHolder[triIndex[i]]);
		}
		indices.push_back(currIndexVec);
		currIndexVec += glm::ivec3(3);
	}
	*/

	fclose(fp);

	return true;

}

void OBJObject::translate(float x, float y, float z) {
	translate(glm::vec3(x, y, z));
}
void OBJObject::translate(glm::vec3 transVec) {
	glm::mat4 translMat(1.0f);
	for (int i = 0; i < 3; ++i) {
		translMat[3][i] += transVec[i];
	}
	model = translMat * model;
}

void OBJObject::rotate(float angle, glm::vec3 axis) {
	/*
	if (glm::length(glm::normalize(axis)) < 1.0f - 1e-4f) {
		std::cout << "Error, axis of rotation given is invalid\n";
		return;
	}
	*/
	// TODO: Check on differences between these two later
	//model = glm::rotate(model, angle, axis);
	//model = glm::rotate(glm::mat4(1.0f), angle, axis) * model;
	glm::mat3 rotMat = glm::rotate(glm::mat4(1.0f), angle, axis);
	glm::mat3 holder = rotMat * glm::mat3(model);
	glm::vec3 transVec = glm::vec3(model[3].x, model[3].y, model[3].z);
	
	model = glm::mat4(holder);
	model[3].x = transVec.x;
	model[3].y = transVec.y;
	model[3].z = transVec.z;
}

void OBJObject::scale(float sx, float sy, float sz) {
	scale(glm::vec3(sx, sy, sz));
}
void OBJObject::scale(glm::vec3 scaleVec) {
	model = glm::scale(model, scaleVec);
}

void OBJObject::reset() {
	model = glm::mat4(1.0f);
}


void OBJObject::draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection) {
	shaderProg.use();
	setShaderToRenderType(shaderProg);
	shaderProg.setMat4("model", model);
	shaderProg.setMat4("view", view);
	shaderProg.setMat4("projection", projection);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (int)indices.size() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
