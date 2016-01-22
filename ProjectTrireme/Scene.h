#pragma once

#include "constdef.h"
#include "Object.h"

#include <fstream>

namespace Trireme
{	
	class Scene
	{
	public:
		Scene();

		Scene(const char* filepath);

		void update();

		void input();

		void draw();

		~Scene();
	private:
		static ushort sceneCount;
		// active camera
		Object* activeCamera;
		// number nodes in scene
		ushort nodeCount;
		// number true objects in the scene, true objects are the unique objects of the scene i.e. there is only one true object for objects with multiple instances
		ushort objectCount; 
		// array of pointers true objects in the scene
		Object** objectArray;
		// the root node, an empty node whose direct children are the highest tier node of the scene
		Node* rootNode; 
	};
}