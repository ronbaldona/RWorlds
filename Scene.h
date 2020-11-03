/* 
   In charge of describing, loading, and rendering scenes
   - RAB
 */
#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Object.h"
#include "Light.h"
#include "Camera.h"
#include "Shader.h"

class Scene
{
	/// <summary>
	/// Loads a scene file into memory
	/// </summary>
	/// <param name="path"> Path of scene file </param>
	void load(const char* path);
public:
	// These are public for now until we design and write some .scene files
	std::vector<Object*> drawables;
	std::vector<Light*> lights;
	std::vector<Camera> cameras;

	/// <summary>
	/// Scene ctor that loads a scene file to memory
	/// </summary>
	/// <param name="path"> Path of scene file </param>
	/// <returns></returns>
	Scene(const char* path);
	~Scene();

	/// <summary>
	/// Draws every drawable object
	/// </summary>
	/// <param name="program"></param>
	/// <param name="view"></param>
	/// <param name="projection"></param>
	void draw(const Shader& program, glm::mat4 view, glm::mat4 projection);
};

