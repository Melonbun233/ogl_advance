#ifndef MESH_H
#define MESH_H
//this is a mesh class that containes an object's vertices, indices and textures
//this class also contains rendering functions
#include <vector>
#include <string>

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
};

struct Texture {
	unsigned int ID;
	std::string type;
	std::string path;

	Texture(unsigned int ID, std::string type, std::string path) :
	ID(ID), type(type), path(path) {}

	Texture() = default;
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
};


class Mesh {
public: 
	//default constructor
	Mesh() = default;
	//complete constructor
	Mesh(std::vector<Vertex> &vertex, std::vector<unsigned int> &index, std::vector<Texture> &tex, 
		Material mat): vertices(vertex), indices(index), textures(tex), material(mat){
			setup();
		}
	//this function should be called every time you changed mesh's data
	void setup();
	//draw the mesh using provided shader
	void render(Shader &shader);
private:
	//rendering data
	unsigned int VAO, VBO, EBO;
	//mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Material material;
};

#endif