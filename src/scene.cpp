#include "scene.h"

using namespace glm;
using namespace std;

SceneID Scene::addModel(const string path)
{
	Model model(path);
	unsigned int id = count ++;
	models.insert({id, model});
	return SceneID(id, MODEL);
}

SceneID Scene::addSpotLight(vec3 direction, vec3 position, float inner, float outer)
{
	SpotLight light(direction, position, inner, outer);
	unsigned int id = count ++;
	spotLights.insert({id, light});
	return SceneID(id, SPOT_LIGHT);
}

SceneID Scene::addSpotLight(vec3 color, vec3 direction, vec3 position, ambient, diffuse, specular,
	float inner, float outer)
{
	SpotLight light(color, direction, position, ambient, diffuse, specular, inner, outer);
	unsigned int id = cout ++;
	spotLights.insert({id, light});
	return SceneID(id, SPOT_LIGHT);
}

SceneID Scene::addDirLight(vec3 direction)
{
	DirLight light(direction);
	unsigned int id = count ++;
	dirLights.insert({id, light});
	return SceneID(id, DIR_LIGHT);
}

SceneID Scene::addDirLight(vec3 color, direction, ambient, diffuse, specular)
{
	DirLight light(color, direction, ambient, diffuse, specular);
	unsigned int id = count ++;
	dirLights.insert({id, light});
	return SceneID(id, DIR_LIGHT);
}

SceneID Scene::addPointLight(vec3 position, float distance)
{
	PointLight(position, distance);
	unsigned int id = count ++;
	pointLights.insert({id, light});
	return SceneID(id, POINT_LIGHT);
}

SceneID Scene::addPointLight(vec3 color, vec3 position, vec3 ambient, vec3 diffuse, 
	vec3 specular, float distance)
{
	PointLight light(color, position, ambient, diffuse, specular, distance);
	unsigned int id = count ++;
	pointLights.insert({id, light});
	return SceneID(id, POINT_LIGHT);
}

void Scene::removeSpotLight(SceneID ID)
{
	if (ID.type == SPOT_LIGHT)
	{
		auto search = spotLights.find(ID.id);
		if (search != spotLights.end())
			spotLights.erase(search);
	} 
}

void Scene::removeDirLight(SceneID ID)
{
	if (ID.type == DIR_LIGHT)
	{
		auto search = dirLights.find(ID.id);
		if (search != dirLights.end())
			dirLights.erase(search);
	}
}

void Scene::removePointLight(SceneID ID)
{
	if (ID.type == POINT_LIGHT)
	{
		auto search = pointLights.find(ID.id);
		if (search != pointLights.end())
			pointLights.erase(search);
	}
}

SpotLight* getSpotLight(SceneID ID)
{
	if (ID.type == SPOT_LIGHT)
	{
		auto search = spotLights.find(ID.id);
		if (search != spotLights.end())
			return &search->second;
	}
	return NULL;
}

DirLight* getDirLight(Scene ID)
{
	if(ID.type == DIR_LIGHT)
	{
		auto search = dirLights.find(ID.id);
		if (search != dirLights.end())
			return &search->second;
	}
	return NULL;
}

PointLight* getPointLight(Scene ID)
{
	if(ID.type == POINT_LIGHT)
	{
		auto search = pointLights.find(ID.id);
		if(search != pointLights.end())
			return &search->second;
	}
	return NULL;
}

