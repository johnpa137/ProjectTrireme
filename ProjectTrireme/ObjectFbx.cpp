#include "ObjectFbx.h"

using namespace Trireme;

using glm::vec3;

FbxManager* Scene::fbxManager = nullptr;
ushort Scene::sceneCount = 0;

Object::Object()
{
	position = vec3();
	rotation = glm::quat();
	scale = vec3(1.f);

	mesh = nullptr;
	camera = nullptr;
}

void Object::setObjectType(FbxNodeAttribute* nodeAttribute)
{
	switch (nodeAttribute->GetAttributeType())
	{
	case FbxNodeAttribute::eMesh:
	{
		setObjectTypeMesh(nodeAttribute);
	}	break;
	case FbxNodeAttribute::eCamera:
	{
		setObjectTypeCamera(nodeAttribute);
	}	break;
	case FbxNodeAttribute::eLight:
	{

	}
	}
}

void Object::setObjectTypeMesh(FbxNodeAttribute* nodeAttribute)
{
	FbxMesh* fMesh = (FbxMesh*)nodeAttribute;

	ushort vertexCount = fMesh->GetControlPointsCount();

	std::vector<vec3> vertices;
	vertices.resize(vertexCount);
	std::vector<unsigned int> indices;

	FbxDouble4* fVertices = fMesh->GetControlPoints();

	for (ushort i = 0; i < vertexCount; ++i)
		for (ushort j = 0; j < 3; ++j)
			vertices[i][j] = float(fVertices[i][j]);

	for (ushort i = 0; i < fMesh->GetPolygonCount(); ++i)
		for (ushort j = 0; j < fMesh->GetPolygonSize(i); ++j)
			indices.push_back(fMesh->GetPolygonVertex(i, j));

	mesh = new Mesh();

	mesh->fill(vertices, indices);
}

void Object::setObjectTypeCamera(FbxNodeAttribute* nodeAttribute)
{
	FbxCamera* fCamera = (FbxCamera*)nodeAttribute;
	
	// vec3 forwardDir = vec3(0.f, 0.f, -1.f);

	// FbxDouble3 d3 = nodeAttribute->GetNode()->LclRotation.Get();
	// vec3 rot3 = vec3(d3[0], d3[1], d3[2]) / 100.f;
	// FbxQuaternion rot4;
	// rot4.ComposeSphericalXYZ(FbxDouble3(rot3[0], rot3[1], rot3[2]));
	// glm::quat rotQ = glm::quat((float)rot4[3], (float)rot4[0], (float)rot4[1], (float)rot4[2]);
	
	// forwardDir = glm::conjugate(rotation) * forwardDir * rotation;

	FbxDouble3 fTarget = fCamera->InterestPosition.Get();
	vec3 target = vec3(fTarget[0], fTarget[1], fTarget[2]);

	camera = new Camera(target);
}

Object::~Object()
{
	if (mesh)
		delete mesh;
	if (camera)
		delete camera;
}

Scene::Scene(const char* filepath, const bool justImportModels, const char* name)
{
	if (!fbxManager)
	{
		// initializing the fbx sdk library
		fbxManager = FbxManager::Create();
		fbxManager->SetIOSettings(FbxIOSettings::Create(fbxManager, IOSROOT));
	}

	FbxImporter* importer = FbxImporter::Create(fbxManager, "");

	if (!importer->Initialize(filepath, -1, fbxManager->GetIOSettings()))
		throw (std::string("Call to FbxImporter::Initialize() failed.\n") +
		std::string("Error: %s\n\n", importer->GetStatus().GetErrorString()));

	scene = FbxScene::Create(fbxManager, name);

	importer->Import(scene);

	importer->Destroy();

	++sceneCount;

	shader0 = new ShaderSimple();
	shader0->compile();

	activeCameraObject = nullptr;

	FbxNode* rootN = scene->GetRootNode();

	for (ushort i = 0; i < rootN->GetChildCount(); ++i)
	{
		FbxNode* node = rootN->GetChild(i);

		nodeToObject(node);
	}
}

void Scene::nodeToObject(FbxNode* node)
{
	objects.push_back(nullptr);

	objects.back() = new Object();

	Object* nodeObject = objects.back();

	nodeObject->name = node->GetName();

	FbxDouble3 d3 = node->LclTranslation.Get();
	nodeObject->position = vec3(d3[0], d3[1], d3[2]);// / 100.f;
	
	d3 = node->LclRotation.Get();
	vec3 rot3 = vec3(d3[0], d3[1], d3[2]);// / 100.f;
	FbxQuaternion rot4;
	rot4.ComposeSphericalXYZ(FbxDouble3(rot3[0], rot3[1], rot3[2]));
	nodeObject->rotation = glm::quat((float)rot4[3], (float)rot4[0], (float)rot4[1], (float)rot4[2]);

	d3 = node->LclScaling.Get();
	nodeObject->scale = vec3(d3[0], d3[1], d3[2]);// / 100.f;

	for (ushort i = 0; i < node->GetNodeAttributeCount(); ++i)
	{
		FbxNodeAttribute* nodeAttribute = node->GetNodeAttributeByIndex(i);
	
		nodeObject->setObjectType(nodeAttribute);

		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::EType::eCamera)
		{
			activeCameraObject = nodeObject;
		}
	}

	for (ushort i = 0; i < node->GetChildCount(); ++i)
	{
		FbxNode* childNode = node->GetChild(i);

		nodeToObject(childNode);
	}
}

void Scene::drawScene()
{
	shader0->bind();
	glUniformMatrix4fv(shader0->uniforms[ShaderSimple::Uniforms::CAMERA_MATRIX], 
		1, GL_FALSE, &activeCameraObject->camera->getViewProjectionMatrix(activeCameraObject->position)[0][0]);
	for (ushort i = 0; i < objects.size(); ++i)
	{
		if (objects[i]->mesh)
		{
			glUniform3fv(shader0->uniforms[ShaderSimple::Uniforms::OBJECTPOSITION],
				1, &objects[i]->position[0]);
			objects[i]->mesh->draw();
		}
	}
}

Scene::~Scene()
{
	activeCameraObject = nullptr;
	--sceneCount;
	if (scene)
		scene->Destroy();
	if (fbxManager && !sceneCount)
		fbxManager->Destroy();
	for (std::vector<Object*>::const_iterator it = objects.cbegin(); it != objects.cend(); ++it)
		delete *it;
	objects.clear();
}