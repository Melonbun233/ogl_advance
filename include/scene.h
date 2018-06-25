#ifndef SCENE_H
#define SCENE_H
//this is a scene class used to store all models, lights and camera
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "model.h"
#include "mesh.h"
#include "light.h"
#include "spotLight.h"
#include "dirLight.h"
#include "pointLight.h"
#include "camera.h"
#include "data.h"


enum OBJECT_TYPE {
	MODEL,
	SPOT_LIGHT,
	DIR_LIGHT,
	POINT_LIGHT
};

struct SceneID {
	const unsigned int id;
	OBJECT_TYPE type;

	SceneID(unsigned int id, OBJECT_TYPE type) : id(id), type(type){}
};


/*
	NOTE: every object in this scene has its own unique id
	NOTE: if you want to explicitly control all objects, call getter functions to get its pointer.
		you can keep this pointer because this pointer will not change even if the hash map used to 
		store the objects rehashed.
	NOTE: every scene may have only one camera
*/

class Scene
{
public:
	//only set the camera
	Scene(const std::string dir, glm::vec3 cam_pos, unsigned int width, unsigned int height) 
	{
		curr_dir = dir;
		vertex_normal = curr_dir + "/../resources/shader/General.vs";
		fragment_normal = curr_dir + "/../resources/shader/General.fs";
		fragment_depth = curr_dir + "/../resources/shader/Depth.fs";
		fragment_single_color = curr_dir + "/../resources/shader/SingleColor.fs";

		single_color_shader = Shader(vertex_normal, fragment_single_color);

		camera = Camera(cam_pos); 
		perspec = 1;
		scrWidth = width;
		scrHeight = height;
	}

	//set object's model view.
	//you can call setPerspec to set the projection of the scene
	//PRE: 
	//	model_id: scene id of the model need to be positioned. this should be valid, otherwise
	//		nothing will be done
	//	model: model matrix used to set the position and scale of the object
	void setModelPos(SceneID model_id, glm::mat4 model);

	//set the projection as perspective or ortho
	//those two functions are not available currently
	//void setPerspective() {perspec = true;}
	//void setOrtho() {perspec = false;}
	//check whether the current view is perspective
	bool isPerspective() {return perspec;}

	//render all models and lights in the scene
	//this function will also update every models' view and projection matrices to fit the camera
	void render();

/*	---------------------------------------------------------------------------------------
	Adder Functions
	---------------------------------------------------------------------------------------	*/
	//add a model into the scene
	//PRE: 
	//	model: model added to the scene
	//POST:
	//	return an unique ID presenting this model
	//	this ID should be kept in order to delete or edit the model
	SceneID addModel(const std::string path);

	//add a standard squre plane at the center of xy plane, this is a model
	//PRE:
	//	mat: material of the plane
	//	tex_path: texture path of 3 different kind of textures. If one texture does't exist,
	//	use empty string. If no texture is used for this plane, use empty vector
	SceneID addPlane(Material&, std::vector<std::string>&);

	SceneID addCube(Material&, std::vector<std::string>&);

	//high light a model by outlining it, model is by default not high lighted
	//PRE:
	//	SceneID: id of the outlined model
	//	vec: color of outlining
	//	bool: whether outlining the model
	//if the SceneID is invalid, nothing will be done
	void setOutline(SceneID, glm::vec3&, bool);


	//add a spot light into the scene
	//PRE: 
	//	direction: direction of the spot light pointing to
	//	position: position of the spot light
	//	inner: angle of the inner side of the edge
	//	outer: angle of the outer side of the edge
	//POST:
	//	return an unique ID presenting this light
	//	this ID should be kept in order to delete or edit the light
	SceneID addSpotLight(glm::vec3 direction, glm::vec3 position, float inner, float outer);

	//this is a more complete spot light adding function
	SceneID addSpotLight(glm::vec3 color, glm::vec3 direction, glm::vec3 position, glm::vec3 ambient,
		glm::vec3 diffuse, glm::vec3 specular, float inner, float outer);

	//passing a existed light, note change the light explicitly will change the light in the scene
	SceneID addSpotLight(SpotLight &light);

	//add a directional light in to the scene
	//PRE:
	//	direction: direction of the light
	//POST:
	//	return an unique ID presenting this light
	//	this ID  shoud be kept in order to delete or edit the light
	SceneID addDirLight(glm::vec3 direction);

	//this is a more complete directional light adding function
	SceneID addDirLight(glm::vec3 color, glm::vec3 direction, glm::vec3 ambient, 
		glm::vec3 diffuse, glm::vec3 specular);

	//passing a existing light, note change the light explicitly will change the light in the scene
	SceneID addDirLight(DirLight &light);


	//add a point light into the scene 
	//PRE:
	//	position: position of the light
	//	distance: range of the light, used to set attenuation
	//POST:
	//	return an unique ID presenting this light
	//	this ID  shoud be kept in order to delete or edit the light
	SceneID addPointLight(glm::vec3 position, float distance);

	//this is a more complete point light adding function
	SceneID addPointLight(glm::vec3 color, glm::vec3 position, glm::vec3 ambient, 
		glm::vec3 diffuse, glm::vec3 specular, float distance);

	//passing a existing light, note change the light explicitly will change the light in the scene
	SceneID addPointLight(PointLight &light);

/*	---------------------------------------------------------------------------------------
	Remover Functions
	---------------------------------------------------------------------------------------	*/

	//remove an object given to its id
	//PRE:
	//	ID: returned id when adding the light into the scene
	//POST:
	//	removing invalid id will result in nothing
	void removeSpotLight(SceneID ID);
	void removePointLight(SceneID ID);
	void removeDirLight(SceneID ID);
	void removeModel(SceneID ID);

/*	---------------------------------------------------------------------------------------
	Getter Functions
	---------------------------------------------------------------------------------------	*/

	//get a light given its id
	//PRE:
	// ID: returned id when adding the light into the scene
	//POST:
	// 	return a pointer points to the light
	//	if the id is invalid, NULL will be returned
	SpotLight*  getSpotLight(SceneID ID);
	DirLight*   getDirLight(SceneID ID);
	PointLight* getPointLight(SceneID ID);
	Model* 		getModel(SceneID ID);
	Camera*		getCamera();



private:

	Shader single_color_shader;
	//fragment and vertex shaders' path
	std::string curr_dir;
	std::string vertex_normal;
	std::string fragment_normal;
	std::string fragment_depth;
	std::string fragment_single_color;

	unsigned int scrWidth;
	unsigned int scrHeight;
	bool perspec; //whether the scene is perspective
	unsigned int count; //this is used for every object's id in the scene
	Camera camera;
	std::unordered_map<unsigned int, Model> models;
	std::unordered_map<unsigned int, SpotLight> spotLights;
	std::unordered_map<unsigned int, DirLight> dirLights;
	std::unordered_map<unsigned int, PointLight> pointLights;

	//set model's view and projection matrices
	//model's position should be set in the setModelPos function
	void setShader(Shader&, glm::mat4, glm::mat4, glm::mat4);

	//send all lights in the scene to models' shaders
	void sendLights(Model &model);

	//manually construct a model 
	Model loadModel(Shader &shader, const float vertices[], const unsigned int indices[], 
		const int vertex_size, const int index_size, Material &mat, std::vector<std::string> &tex_path);

	//get projection matrix
	glm::mat4 getProjMat();

};

#endif