#ifndef SCENE_H
#define SCENE_H
//this is a scene class used to store all models, lights and camera
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"
#include "shader.h"
#include "model.h"
#include "light.h"
#include "spotLight.h"
#include "dirLight.h"
#include "pointLight.h"

enum OBJECT_TYPE {
	MODEL,
	SPOT_LIGHT,
	DIR_LIGHT,
	POINT_LIGHT
};

struct SceneID {
	const unsigned int id;
	OBJECT_TYPE type;
}

//NOTE: every object in this scene has its own unique id

class Scene
{
public:
	//default constructor
	//only set the camera
	Scene(Camera camera) : camera(camera), ID(0) {}

	//add a model into the scene
	//PRE: 
	//	model: model added to the scene
	//POST:
	//	return an unique ID presenting this model
	//	this ID should be kept in order to delete or edit the model
	SceneID addModel(const std::string path);

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


	//remove a light given to its id
	//PRE:
	//	ID: returned id when adding the light into the scene
	//POST:
	//	removing invalid id will result in nothing
	void removeSpotLight(SceneID ID);
	void removePointLight(SceneID ID);
	void removeDirLight(SceneID ID);

	//get a light given its id
	//PRE:
	// ID: returned id when adding the light into the scene
	//POST:
	// 	return a pointer points to the light
	//	if the id is invalid, NULL will be returned
	SpotLight*  getSpotLight(SceneID ID);
	DirLight*   getDirLight(SceneID ID);
	PointLight* getPointLight(SceneID ID);



private:
	unsigned int count; //this is used for every objects in the scene
	Camera camera;
	std::unordered_map<unsigned int, Model> models;
	std::unordered_map<unsigned int, SpotLight> spotLights;
	std::unordered_map<unsigned int, DirLight> dirLights;
	std::unordered_map<unsigned int, PointLight> pointLights;

};

#endif