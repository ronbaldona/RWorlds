#include "Model.h"
#include "PrintDebug.h"

Model::Model(const char* path) : Object() {
	model = glm::mat4(1.0f);
	if (!load(path)) {
		std::cout << "Exiting program...\n";
		exit(EXIT_FAILURE);
	}
	centerToOrigin();
}

Model::~Model() {
	for (auto mesh : meshes) {
		glDeleteBuffers(1, &mesh.VBO);
		glDeleteBuffers(1, &mesh.EBO);
		glDeleteVertexArrays(1, &mesh.VAO);
	}
}

void Model::draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection) {
	shaderProg.use();
	setShaderToRenderType(shaderProg);
	for (auto mesh : meshes) {
		mesh.draw(shaderProg, model, view, projection);
	}
}

bool Model::load(const char* path) {
	Assimp::Importer import;
	// TODO: Add more flags later?
	const aiScene* scene = import.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);

	// Check if loading has failed (incomplete, no root node to load)
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
		!scene->mRootNode) {
		std::cout << "Error in assimp loading model!\n" << import.GetErrorString();
		std::cout << std::endl;
		return false;
	}
	std::string sPath = std::string(path);
	directory = sPath.substr(0, sPath.find_last_of('/'));

	// Recursively move through scene graph
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	//TODO: ADD SCENE GRAPH TRANSFORMATION IMPLEMENTATIONS
	//At the moment, this can only work for 1 node objects.
	
	// Process each mesh within the node (node actual contains mesh INDICES)
	for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// Traverse scene graph
	for (unsigned int i = 0; i < node->mNumChildren; ++i) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// Load vertex info
	Vertex vertex;
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		vertex.position = glm::vec3(
			mesh->mVertices[i].x, 
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		vertex.normal = glm::normalize(
			glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y, 
				mesh->mNormals[i].z
			)
		);

		if (mesh->HasTextureCoords(0)) {
			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y);
		}
		else 
			vertex.texCoords = glm::vec2(0);
		
		vertices.push_back(vertex);
	}

	// Load indices
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	/*
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	*/
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, 
	aiTextureType type, std::string typeName) {

	std::vector<Texture> textures;
	/*
	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = TextureFromFile(str.C_Str(), directory);
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);
	}
	*/
	return textures;
}

void Model::translate(float x, float y, float z) {
	translate(glm::vec3(x, y, z));
}
void Model::translate(glm::vec3 transVec) {
	glm::mat4 translMat(1.0f);
	for (int i = 0; i < 3; ++i) {
		translMat[3][i] += transVec[i];
	}
	model = translMat * model;
}

void Model::rotate(float angle, glm::vec3 axis) {
	/*
	if (glm::length(glm::normalize(axis)) < 1.0f - 1e-4f) {
		std::cout << "Error, axis of rotation given is invalid\n";
		return;
	}
	*/
	glm::mat3 rotMat = glm::rotate(glm::mat4(1.0f), angle, axis);
	glm::mat3 holder = rotMat * glm::mat3(model);
	glm::vec3 transVec = glm::vec3(model[3].x, model[3].y, model[3].z);

	model = glm::mat4(holder);
	model[3].x = transVec.x;
	model[3].y = transVec.y;
	model[3].z = transVec.z;
}

void Model::scale(float sx, float sy, float sz) {
	scale(glm::vec3(sx, sy, sz));
}
void Model::scale(glm::vec3 scaleVec) {
	model = glm::scale(model, scaleVec);
}

void Model::reset() {
	model = glm::mat4(1.0f);
}

void Model::centerToOrigin() {
	std::vector<glm::vec3> minDimVec;
	std::vector<glm::vec3> maxDimVec;
	glm::vec3 min(std::numeric_limits<float>::max());
	glm::vec3 max(std::numeric_limits<float>::lowest());
	
	// Find minimum and maximum position values of the model
	for (auto const& mesh : meshes) {
		glm::vec3 minHolder, maxHolder;
		mesh.getCornerVecs(minHolder, maxHolder);
		minDimVec.push_back(minHolder);
		maxDimVec.push_back(maxHolder);
	}
	for (int i = 0; i < minDimVec.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			min[j] = (min[j] > minDimVec[i][j]) ? minDimVec[i][j] : min[j];
			max[j] = (max[j] < maxDimVec[i][j]) ? maxDimVec[i][j] : max[j];
		}
	}

	// Translate each point in the mesh to the center
	glm::vec3 translate(
		0.5f * (max.x + min.x),
		0.5f * (max.y + min.y),
		0.5f * (max.z + min.z)
	);
	for (auto& mesh : meshes) {
		for (auto& vertex : mesh.vertices) {
			vertex.position -= translate;
		}
		mesh.updateBuffers();
	}
}

void Model::sendMatToShader(const Shader& program) const {
	for (const auto& mesh : meshes)
		mesh.sendMatToShader(program);
}
