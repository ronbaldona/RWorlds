/* 
   In charge of describing, loading, and rendering scenes
   - RAB
 */
#pragma once

#include <vector>

#include "Object.h"
#include "Light.h"
#include "Camera.h"

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


};

