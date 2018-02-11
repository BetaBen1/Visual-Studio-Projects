#include "Mesh.h"
#include "Obj_Loader.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{

	IndexedModel model;
	
	//m_drawcount = numvertices;
	/*
	m_drawcount = numindices;

	glgenvertexarrays(1, &m_vertexarrayobject);
	glbindvertexarray(m_vertexarrayobject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;

	positions.reserve(numvertices);
	texcoords.reserve(numvertices);
	*/

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}

	for (unsigned int i = 0; i < numIndices; i++) 
	{
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);

	/*
	glgenbuffers(num_buffers, m_vertexarraybuffers);
	glbindbuffer(gl_array_buffer, m_vertexarraybuffers[position_vb]);
	glbufferdata(gl_array_buffer, numvertices*sizeof(positions[0]), &positions[0], gl_static_draw);

	glenablevertexattribarray(0);
	glvertexattribpointer(0, 3, gl_float, gl_false, 0, 0);

	glbindbuffer(gl_array_buffer, m_vertexarraybuffers[texcoord_vb]);
	glbufferdata(gl_array_buffer, numvertices * sizeof(texcoords[0]), &texcoords[0], gl_static_draw);

	glenablevertexattribarray(1);
	glvertexattribpointer(1, 2, gl_float, gl_false, 0, 0);

	glbindbuffer(gl_element_array_buffer, m_vertexarraybuffers[index_vb]);
	glbufferdata(gl_element_array_buffer, numindices * sizeof(indices[0]), &indices[0], gl_static_draw);

	glbindvertexarray(0);
	*/

}

Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
}


void Mesh::Draw() 
{
	glBindVertexArray(m_vertexArrayObject);

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);

}
