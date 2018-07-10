#ifndef MODEL_H
#define MODEL_H
//this is a model class
//each model may contain one or more meshes
#include <string>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "mesh.h"
#include "shader.h"


class Model 
{
public:
	//constructor provided with a path indicatin where the model is, process the model
	//with assimp
	Model(const std::string &path, Shader &shader) : shader(shader)
	{
		loadAiModel(path);
		model = glm::mat4(1.0);
		pos = glm::vec3(0.0);
		rotate_angle = 0;
		rotate = glm::vec3(1.0);
		scale = glm::vec3(1.0);
	}

	//manually provide vertices' positions, normals, texture coordinates maeterial and texture file path
	//Do NOT use this function if you don't know how to use and the consequences
	//PRE:
	//	shader: shader for this model
	//	position: all vertices' positions in vectors
	//	normal: all vertices' normals in vectors, the order should be cooresponding to position array
	//	index: order of all vertices when drawing
	//	coord: all texture coordinates cooresponding to each vertices
	//	tex_path: this vector should contain exactly 0 or 3 paths. ambient, diffude and specular textures,
	// 		they should be in the same directory, if the texture doesn't exist, use empty string
	//		if this model doesn't contain any texture, use empty vector
	//NOTE: the size of the positions, normals and coords arrays should have exactly the same size
	Model(Shader &shader, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
		std::vector<unsigned int> &indices, std::vector<glm::vec2>  coords, Material &mat,
		std::vector<std::string> &tex_path) : shader(shader)
	{
		loadManualModel(positions, normals, indices, coords, mat, tex_path);
		model = glm::mat4(1.0);
		pos = glm::vec3(0.0);
		rotate_angle = 0;
		rotate = glm::vec3(1.0);
		scale = glm::vec3(1.0);
	}


	//call this function to render the model with default shader
	void render();
	//render the model with a provided shader
	void render(Shader&);

	//directory of this model. All other textures should be in the same directory
	std::string directory;
	//shader used for this model
	Shader shader;
	
	//calculate model view according to translation, rotation, and scaling
	void calcModelView();
	//initialize the position, rotation, and scaling vector
	glm::mat4 model;
	glm::vec3 pos, rotate, scale;
	float rotate_angle;

	std::vector<Mesh> meshes;

	//whether transparent
	bool transparent;
	//outlining functionality
	bool outlined = false;
	//model outlining color
	glm::vec3 outline_color;

private:
	//store loaded textures to optimize
	std::vector<Texture> textures_loaded; 
	//whether the model is outlined


	//load the model using assimp
	void loadAiModel(const std::string path);

	//load the model with raw datas and textures
	void loadManualModel(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
		std::vector<unsigned int> &indices, std::vector<glm::vec2> &coords, Material &mat, 
		std::vector<std::string> &tex_path);
	//recursively process each node and it's children
	void processNode(aiNode *node, const aiScene *scene);
	//process a specific mesh to our defined mesh object
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	//used to load ai material texture
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
		const std::string name);
	//both functions used to load textures
	unsigned int loadTexture(const std::string &path, const std::string &directory);
	unsigned int loadTexture(const std::string);


};

#endif