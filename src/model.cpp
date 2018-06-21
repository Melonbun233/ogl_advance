#include "model.h"

using namespace std;
using namespace Assimp;
using namespace glm;

void Model::render()
{
	shader.use();
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].render(shader);
}

void Model::loadAiModel(const string path)
{
	Importer importer;
	//get scene using assimp
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | 
		aiProcess_FlipUVs);
	//check scene
	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::loadManualModel(vector<vec3> &positions, vector<vec3> &normals,
	vector<unsigned int> &indices, vector<vec2> &coords, Material &mat, vector<string> &tex_path)
{
	vector<Vertex> vertices;
	vector<Texture> textures;

	//proceed all vertices
	for (int i = 0; i < positions.size(); i ++)
		vertices.push_back(Vertex(positions[i], normals[i], coords[i]));
	//check texture string
	if (tex_path.size() == 3) { //this model doesn't contain texture
		if (tex_path[0] != "") //existing ambient texture
		{
			unsigned int ambient = loadTexture(tex_path[0]);
			textures.push_back(Texture(ambient, "ambient", tex_path[0]));
		}
		if(tex_path[1] != "") //existing diffuse texture
		{
			unsigned int diffuse = loadTexture(tex_path[1]);
			textures.push_back(Texture(diffuse, "diffuse", tex_path[1]));
		}
		if(tex_path[2] != "") //existing specular texture
		{
			unsigned int specular = loadTexture(tex_path[2]);
			textures.push_back(Texture(specular, "specular", tex_path[2]));
		}
	}
 
	meshes.push_back(Mesh(vertices, indices, textures, mat));
}

void Model::processNode(aiNode *root, const aiScene *scene)
{
	//process all root's meshes
	for(unsigned int i = 0; i < root->mNumMeshes; i ++)
	{
		aiMesh *mesh = scene->mMeshes[root->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	//recursively call this function to it's children
	for(unsigned int i = 0; i < root->mNumChildren; i ++)
	{
		processNode(root->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	//process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i ++)
	{
		Vertex vertex;
		vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		//check if the vertex has texture coordinates
		if (mesh->mTextureCoords[0])
			vertex.texCoords = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y); 
			//we only consider the first set of texture coordinates
		else
			vertex.texCoords = vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	//process indices
	//every face is processed into triangle
	for (unsigned int i = 0; i < mesh->mNumFaces; i ++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//process textures
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	//load all ambient maps to textures
	vector<Texture> ambientMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, 
		"ambient");
	textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
	//load all diffuse maps to textures
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, 
		"diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//load all specular maps to textures
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR,
		"specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	//process material
	aiColor3D ambient, diffuse, specular;
	float shininess;
	material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	material->Get(AI_MATKEY_SHININESS, shininess);

	Material mat = {vec3(ambient.r, ambient.g, ambient.b), 
					vec3(diffuse.r, diffuse.g, diffuse.b),
					vec3(specular.r, specular.g, specular.b),
					shininess};
	return Mesh(vertices, indices, textures, mat);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *material, aiTextureType type, 
	string type_name)
{
	vector<Texture> textures;
	
	for (unsigned int i = 0; i < material->GetTextureCount(type); i ++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		//check whether the texture is already loaded
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)//loop all loaded textures
		{
			if (strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		//texture already loaded
		if(!skip)
		{
			Texture texture = {loadTexture(str.C_Str(), directory), type_name, str.C_Str()};
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

unsigned int Model::loadTexture(const string &path, const string &directory)
{
	string filename = directory + '/' + path;
	return loadTexture(filename);
}

unsigned int Model::loadTexture(const string filename)
{
	unsigned int ID;
	glGenTextures(1, &ID);

	int width, height, channels;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	if (data)
	{
		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//configure texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
	else
	{
		cout << "Texture failed to load at path: " << endl << filename << endl;
		stbi_image_free(data);
	}

	return ID;
}


