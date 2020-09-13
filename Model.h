/*  Assimp object loader that loads the full model 
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
	/// 
	/// </summary>
	/// <param name="node"></param>
	/// <param name="scene"></param>
	void processNode(aiNode* node, const aiScene* scene);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="mesh"></param>
	/// <param name="scene"></param>
	/// <returns></returns>
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="mat"></param>
	/// <param name="type"></param>
	/// <param name="typeName"></param>
	/// <returns></returns>
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	Model(const char* path);

	// Destructor. Deletes every mesh and buffer associated with said mesh
	~Model();

	/// <summary>
	/// Draw object to screen
	/// </summary>
	/// <param name="shaderProg"></param>
	/// <param name="proj"></param>
	/// <param name="projection"></param>
	void draw(Shader shaderProg, glm::mat4 proj, glm::mat4 projection);

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
