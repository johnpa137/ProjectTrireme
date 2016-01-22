#include "Scene.h"

using namespace Trireme;

ushort Scene::sceneCount = 0;

Scene::Scene()
{
	nodeCount = 0;
	objectCount = 0;
	objectArray = nullptr;
	rootNode = nullptr;
}

Scene::Scene(const char* filepath) : Scene::Scene()
{

}

Scene::~Scene()
{
	if (objectArray)
		for (ushort i = 0; i < objectCount; ++i)
			if (objectArray[i])
				delete objectArray[i];
		delete[] objectArray;

}