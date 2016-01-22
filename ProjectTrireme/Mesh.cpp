#include "Mesh.h"

using namespace Trireme;

using glm::vec3;

Mesh::Mesh()
{
	vao = NULL;
	std::fill_n(vbo, ushort(MAX_BUFFER_COUNT), NULL);
	vertexCount = 0;
}

void Mesh::bind()
{
	glBindVertexArray(vao);
}

void Mesh::fill(std::vector<vec3> vertices, std::vector<unsigned int> indices)
{
	if (!vao)
		glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(MAX_BUFFER_COUNT, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
	// enables this vertex attribute in the openGL program, basically the variable in the glsl
	// file
	glEnableVertexAttribArray(Shader::Attribs::VERTEX);
	// attribute, number of elements in each element(vec3), whether it's normalized, 
	// amount to skip each step, amount to skip at start
	glVertexAttribPointer(Shader::Attribs::VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(NULL);

	vertexCount = vertices.size();
	indexCount = indices.size();
}

void Mesh::draw()
{
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	// glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(NULL);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(MAX_BUFFER_COUNT, vbo);
}
