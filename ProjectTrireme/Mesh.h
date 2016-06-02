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
		UVMap(std::vector<glm::vec2> uvs){ this->uvs = uvs.data(); }
		UVMap(glm::vec2* pUVs){ this->uvs = uvs; }
		glm::vec2* uvs;
		~UVMap(){ delete[] uvs; }
	};
	
	class Mesh
	{
	public:
		Mesh();

		void bind()const;

		void addUVMap(std::vector<glm::vec2> uvs);

		void addUVMap(glm::vec2* uvs);

		void addUVMap(UVMap uvMap);

		// void addBuffer(GLenum bufferType, GLsizeiptr datasize, const void* data, GLenum usage, uint16_t shaderAttribIndex, uint16_t attribsize);

		void draw()const;

		virtual ~Mesh();
	private:
		GLuint vao;
		GLuint* vbo;

		uint16_t vertexCount;
		uint16_t indexCount;
		uint16_t bufferCount;

		UVMap* uvMaps;
	};
}

#endif


