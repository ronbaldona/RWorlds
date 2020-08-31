/*
    Interface class that handles loading the shaders and containing all the models for 
	each particular scene.
    - RAB
 */
#pragma once

#include "OBJObject.h"
#include "Shader.h"

class Scene
{
	std::vector<Object*> models;
	std::vector<Shader*> shaders;

	bool loadSceneFromFile(const char* filepath);

public:
	Scene();
	~Scene();

	Scene(const char* filepath);


};

