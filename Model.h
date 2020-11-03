/*  Assimp object loader that loads a full model based out of meshes. Will be
    expanded to load textures
    - RAB
 */
#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Object.h"

class Model : public Object {
	std::vector<Mesh> meshes;
	std::string directory;

	/// <summary>
	/// Loads object from given file
	/// </summary>
	/// <param name="path"> File path name of object </param>
	/// <returns> True if successful, Otherwise false </returns>
	bool load(const char* path);

	/// <summary>
	/// Processes each aiNode scene. Can be called recursively
	/// </summary>
	/// <param name="node"> ptr to aiNode </param>
	/// <param name="scene"> ptr to aiScene </param>
	void processNode(aiNode* node, const aiScene* scene);
	/// <summary>
	/// Processes a passed in aiMesh
	/// </summary>
	/// <param name="mesh"> ptr to an aiMesh </param>
	/// <param name="scene"> ptr to an aiScene object </param>
	/// <returns> Mesh object </returns>
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	/// <summary>
	/// Loads material textures
	/// </summary>
	/// <param name="mat"> ptr to aiMaterial </param>
	/// <param name="type"> enum that denotes texture type </param>
	/// <param name="typeName"> string name of texture type </param>
	/// <returns></returns>
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

public:
	/// <summary>
	/// Constructor that loads an object from a given file
	/// </summary>
	/// <param name="path"> file path of object to load </param>
	/// <returns> N/A </returns>
	Model(const char* path);

	// Destructor. Deletes every mesh and buffer associated with said mesh
	~Model();

	/// <summary>
	/// Draw object to screen. 
	/// </summary>
	/// <param name="program"> Shader program </param>
	/// <param name="view"> view matrix </param>
	/// <param name="projection"> projection matrix </param>
	void draw(const Shader& program, glm::mat4 view, glm::mat4 projection);

	/// <summary>
	/// Centers object to origin
	/// </summary>
	void centerToOrigin();

	/// <summary>
    /// Sends material info to the passed-in shader
    /// </summary>
    /// <param name="program"></param>
	void sendMatToShader(const Shader& program) const;
};
