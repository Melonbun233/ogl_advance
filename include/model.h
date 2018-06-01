#ifndef MODEL_H
#define MODEL_H
//this is a model class
//each model may contain one or more meshes
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"
#include "glm/glm.hpp"
#include "mesh.h"
#include "shader.h"


class Model 
{
public:
	//constructor provided with a path indicatin where the model is
	Model(const std::string &path) {loadModel(path);}
	//call this function to render the model with provided shader
	void render(Shader shader);
	//model data
	std::vector<Mesh> meshes;
	//store loaded textures to optimize
	std::vector<Texture> textures_loaded; 
	std::string directory;

private:
	//load the model using assimp
	void loadModel(const std::string path);
	//recursively process each node and it's children
	void processNode(aiNode *node, const aiScene *scene);
	//process a specific mesh to our defined mesh object
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	//used to load material texture
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
		const std::string name);
	//get texture id
	unsigned int getTextureID(const std::string &path, const std::string &directory);
};

#endif