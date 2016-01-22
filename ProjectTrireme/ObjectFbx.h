// the fbx sdk blows for anything other than simple meshes
#pragma once

#include "constdef.h"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\quaternion.hpp"
#include "fbxsdk.h"

#include "Camera.h"
#include "Mesh.h"

#include <string>
#include <vector>

namespace Trireme
{
	// An object in the scene with 3d coordinates
	class Object
	{
	public:
		enum Types{
			CAMERA,
			MESH,
			ARMATURE,
			LIGHT,
			UNKNOWN,
			TYPE_COUNT
		};

		Object();

		void setObjectType(FbxNodeAttribute* nodeAttribute);
		void setObjectTypeMesh(FbxNodeAttribute* nodeAttribute);
		void setObjectTypeCamera(FbxNodeAttribute* nodeAttribute);

		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
		const char* name;

		Mesh* mesh;
		Camera* camera;

		~Object();
	};

	class Scene
	{
	public:
		// create an empty scene
		Scene();
		
		// import a scene from a file
		Scene(const char* filepath, const bool justImportModels = false, const char* name = "scene");

		void drawScene();

		~Scene();
	private:
		static ushort sceneCount;
		static FbxManager* fbxManager;
		Object* activeCameraObject;
		FbxScene* scene;
		ShaderSimple* shader0;
		std::vector<Object*> objects;
		void nodeToObject(FbxNode* node);
	};

}