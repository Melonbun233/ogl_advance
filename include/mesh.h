#ifndef MESH_H
#define MESH_H
//this is a mesh class that containes an object's vertices, indices and textures
//this class also contains rendering functions
#include <vector>
#include <string>
#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shader.h"
#include "glm/glm.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 coord) : 
	position(position), normal(normal), texCoords(coord) {}

	Vertex() = default;
	//overload << operator for debugging
	friend std::ostream& operator<< (std::ostream &os, const Vertex &vertex)
	{
		os << "position: (" << vertex.position.x << ", " << vertex.position.y << ", " << 
			vertex.position.z << ")" << std::endl;
		os << "normal: (" << vertex.normal.x << ", " << vertex.normal.y << ", " << 
			vertex.normal.z << ")" << std::endl;
		os << "tex coords: (" << vertex.texCoords.x << ", " << vertex.texCoords.y << ")" << std::endl;
		return os;
	} 
};

struct Texture {
	unsigned int ID;
	std::string type;
	std::string path;

	Texture(unsigned int ID, std::string type, std::string path) :
	ID(ID), type(type), path(path) {}

	Texture() = default;
	//overload << operator for debugging
	friend std::ostream& operator<< (std::ostream &os, const Texture tex)
	{
		os << "texture ID: " << tex.ID << ", type: " << tex.type << ", path: " << tex.path << std::endl;
		return os;
	}
};

//material for this mesh
struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
	ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

	Material() = default;
	//overload << operator for debugging
	friend std::ostream& operator<< (std::ostream &os, const Material &mat)
	{
		os << "ambient: (" << mat.ambient.x << ", " << mat.ambient.y << ", " << 
			mat.ambient.z << ")" << std::endl;
		os << "diffuse: (" << mat.diffuse.x << ", " << mat.diffuse.y << ", " << 
			mat.diffuse.z << ")" << std::endl;
		os << "specular: (" << mat.specular.x << ", " << mat.specular.y << ", " << 
			mat.specular.z << ")" << std::endl;
		os << "shininess: " << mat.shininess;
		return os;
	}
};


class Mesh {
public: 
	//default constructor
	Mesh() = default;
	//complete constructor
	Mesh(std::vector<Vertex> &vertex, std::vector<unsigned int> &index, std::vector<Texture> &tex, 
		Material &mat): vertices(vertex), indices(index), textures(tex), material(mat){
			setup();
		}
	//this function should be called every time you changed mesh's data
	void setup();
	//draw the mesh using provided shader
	void render(Shader &shader);

	//overload << operator for debugging
	friend std::ostream& operator<< (std::ostream&, const Mesh&);

	//mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Material material;

private:
	//rendering data
	unsigned int VAO, VBO, EBO;
};

#endif