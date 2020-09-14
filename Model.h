/*  Assimp object loader that loads a full model
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
	/// Draw object to screen. DEPRECATED
	/// </summary>
	/// <param name="shaderProg"> Shader program </param>
	/// <param name="view"> view matrix </param>
	/// <param name="projection"> projection matrix </param>
	void draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection);

	/// <summary>
	/// Translates the object
	/// </summary>
	/// <param name="x"> value to translate along x-axis </param>
	/// <param name="y"> value to translate along y-axis </param>
	/// <param name="z"> value to translate along z-axis </param>
	void translate(float x, float y, float z);
	/// <summary>
	/// Translates the object
	/// </summary>
	/// <param name="transVec"> translation vals along axis </param>
	void translate(glm::vec3 transVec);

	/// <summary>
	/// Rotate the object
	/// </summary>
	/// <param name="angle"> angle of rotation </param>
	/// <param name="axis"> axis of rotation </param>
	void rotate(float angle, glm::vec3 axis);

	/// <summary>
	/// Scale object
	/// </summary>
	/// <param name="sx"> scale val along x </param>
	/// <param name="sy"> scale val along y </param>
	/// <param name="sz"> scale val along z </param>
	void scale(float sx, float sy, float sz);
	/// <summary>
	/// Scale object
	/// </summary>
	/// <param name="scaleVec"> scale vals along axis </param>
	void scale(glm::vec3 scaleVec);

	/// <summary>
	/// Resets object's transformations
	/// </summary>
	void reset();
};
