#include "../include/mesh.h"
using namespace std;
using namespace glm;

void Mesh::setup()
{
	//generating vao, vbo and ebo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//setting up VAO
	glBindVertexArray(VAO);
	//setting up VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	//setting up EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	//VAO arribute pointers
	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)0);
	//normal positions
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
		(void*)offsetof(Vertex, normal));
	//texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
		(void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

void Mesh::render(Shader &shader)
{
	//counters uesd for texture name
	unsigned int counter_amb = 0;
	unsigned int counter_diff = 0;
	unsigned int counter_spec = 0;
//	unsigned int counter_emis = 0; //this is currently not used
	for (unsigned int i = 0; i < textures.size(); i ++) 
	{
		glActiveTexture(GL_TEXTURE0 + i); 
		string name;
		if(textures[i].type == "ambient")
			name = "ambient[" + to_string(counter_amb++) + "]";
		else if(textures[i].type == "diffuse")
			name = "diffuse[" + to_string(counter_diff++) + "]";
		else if(textures[i].type == "specular")
			name = "specular[" + to_string(counter_spec++) + "]";
		//else if(textures[i].type == emission)
		//	name = "emission[" + to_string(counter_emis++) + "]";
		shader.setInt("material." + name, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}
	//update texture numbers
	shader.setInt("material.amb_num", counter_amb);
	shader.setInt("material.diff_num", counter_diff);
	shader.setInt("material.spec_num", counter_spec);
	shader.setVec3("material.ambient", material.ambient);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setFloat("material.shininess", material.shininess);
	//draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

std::ostream& operator<< (std::ostream &os, const Mesh &mesh)
{
	//vertices
	os << "Vertices num: " << mesh.vertices.size() << endl;
	for (int i = 0; i < mesh.vertices.size(); i ++)
	{
		os << "vertices[" << i << "]:" << endl;
		os << mesh.vertices[i] << endl;
	}
	//indices
	os << "Indices num: " << mesh.indices.size() << endl;
	for (int i = 0; i < mesh.indices.size(); i ++)
	{
		os << mesh.indices[i] << " ";
	}
	os << endl << endl;
	//textures
	os << "Textures num: " << mesh.textures.size() << endl;
	for (int i = 0; i < mesh.textures.size(); i ++)
	{
		os << "textures[" << i << "]: " << endl;
		os << mesh.textures[i] << endl;
	}
	//material
	os << "Material: " << endl;
	os << mesh.material << endl;
	return os;
}
