#ifndef TRIREME_MESH_H
#define TRIREME_MESH_H

#include "constdef.h"
#include "glm\glm.hpp"
#include "GL\glew.h"

#include "Shader.h"

#include <vector>

namespace Trireme
{
	struct UVMap
	{
		UVMap(){}
		UVMap(std::vector<glm::vec2> pUVs){ uvs = pUVs.data(); }
		glm::vec2* uvs;
		~UVMap(){ delete[] uvs; }
	};
	
	class Mesh
	{
	public:
		enum Buffers
		{
			VERTEX_BUFFER,
			UV_BUFFER,
			NORMAL_BUFFER,
			TANGENT_BUFFER,
			WEIGHT_BUFFER,
			WEIGHT_INDEX_BUFFER,
			INDEX_BUFFER,
			MAX_BUFFER_COUNT
		};

		Mesh();

		void bind()const;

		void fill(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);

		void addUVMap(std::vector<glm::vec2> uvs);

		void addUVMap(UVMap uvMap);

		void draw()const;

		virtual ~Mesh();
	private:
		GLuint vao;
		GLuint vbo[MAX_BUFFER_COUNT];

		ushort vertexCount;
		ushort indexCount;

		std::vector<UVMap> uvMaps;
	};
}

#endif


