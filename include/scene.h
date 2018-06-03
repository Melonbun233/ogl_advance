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
	SceneID addModel(Model model);

	//add a spot light into the scene
	//PRE: 
	//	light: spot light added into the scene
	//POST:
	//	return an unique ID presenting this light
	//	this ID should be kept in order to delete or edit the light
	SceneID addSpotLight(SpotLight light);

	//add a directional light in to the scene
	//PRE:
	//	light: directional light added into the scene
	//POST:
	//	return an unique ID presenting this light
	//	this ID  shoud be kept in order to delete or edit the light
	SceneID addDirLight(DirLight light);


	//add a point light into the scene 
	//PRE:
	//	light: point light added into the scene
	//	return an unique ID presenting this light
	//	this ID  shoud be kept in order to delete or edit the light
	SceneID addPointLight(PointLight light);

	//remove a light according to its id
	//PRE:
	//	ID: returned id when adding the light into the scene
	//POST:
	//	removing invalid id will not result in anything
	void removeLight(SceneID ID);

	//update a specific light in the scene finding by its id
	//PRE:
	//	ID: id of the light, this should be valid. Otherwise no change will be made
	//	light: updated light obeject
	void updateLight(SceneID ID, Light light);


private:
	unsigned int count; //this is used for every objects in the scene
	Camera camera;
	std::unordered_map<unsigned int, Model> models;
	std::unordered_map<unsigned int, SpotLight> spotLights;
	std::unordered_map<unsigned int, DirLight> dirLights;
	std::unordered_map<unsigned int, PointLight> pointLights;

};

#endif