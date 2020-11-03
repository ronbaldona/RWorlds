#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>

void Scene::load(const char* path) {}

Scene::Scene(const char* path) {
	load(path);
}

Scene::~Scene() {
	// Clear all dynamically allocated data and ensure no access
	for (auto drawablePtr : drawables)
		delete drawablePtr;
	drawables.clear();
	for (auto lightPtr : lights)
		delete lightPtr;
	lights.clear();
}


