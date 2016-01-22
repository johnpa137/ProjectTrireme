#include "constdef.h"
#include "glm\glm.hpp"
#include "glm\gtc\quaternion.hpp"

#include <vector>
#include <string>

namespace Trireme
{
	// a scene node indicating parent and child relations between objects
	struct Node
	{
		Node* parent;
		Node** children;
		ushort childCount;
		Object* content; // reference to object this node is referencing
	};
	
	// a class containing the 3d orientation of scene objects such as
	// meshes, cameras, lights etc.
	class Object
	{
	public:
		enum ReferenceType
		{
			REFERENCE_COUNT
		};

		Object();

		Node* node;

		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		~Object();
	};

	class MeshObject : public Object
	{
	public:
		// node children will reference these in such order
		// node->children[0] will be a uv_layer if it's childCount is 0, 
		// or empty with an array of uv_layers as children if its childCount > 0
		// and so on
		// node->children[3] will be a nullptr if there's no armature attached to
		// this mesh
		enum ReferenceType
		{
			UV_LAYERS = Object::ReferenceType::REFERENCE_COUNT,
			TEXTURE_LAYERS,
			MATERIAL_LAYERS,
			ARMATURE_LAYERS,
			SHAPE_KEY_LAYERS,
			VERTEX_COLOR_LAYERS,
			REFERENCE_COUNT
		};

		MeshObject();
		
		~MeshObject();
	};
}
