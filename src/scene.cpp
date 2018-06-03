#include "scene.h"

SceneID Scene::addModel(Model model)
{
	unsigned int id = count ++;
	models.insert({id, model});
	return SceneID(id, MODEL);
}

SceneID Scene::addSpotLight(SpotLight light)
{
	unsigned int id = count ++;
	spotLights.insert({id, light});
	return SceneID(id, SPOT_LIGHT);
}

SceneID Scene::addDirLight(DirLight light)
{
	unsigned int id = count ++;
	dirLights.insert({id, light});
	return SceneID(id, DIR_LIGHT);
}

SceneID Scene::addPointLight(PointLight light)
{
	unsigned int id = count ++;
	pointLights.insert({id, light});
	return SceneID(id, POINT_LIGHT);
}

void Scene::removeLight(SceneID ID)
{
	if (SceneID.type == SPOT_LIGHT)
	{
		auto search = spotLights.find(ID.id);
		if (search != spotLights.end())
			spotLights.erase(search);
	} 
	else if (SceneID.type == DIR_LIGHT)
	{
		auto search = dirLights.find(ID.id);
		if (search != dirLights.end())
			dirLights.erase(search);
	}
	else if (SceneID.type == POINT_LIGHT)
	{
		auto search = pointLights.find(ID.id);
		if (search != pointLights.end())
			pointLights.erase(search);
	}
}

void Scene::updateLight(SceneID ID, Light light)
{
	if (SceneID.type == SPOT_LIGHT)
	{
		auto search = spotLights.find(ID.id);
		if (search != spotLights.end())
			search->second = (SpotLight)light;
	} 
	else if (SceneID.type == DIR_LIGHT)
	{
		auto search = dirLights.find(ID.id);
		if (search != dirLights.end())
			search->second = (DirLight)light;
	}
	else if (SceneID.type == POINT_LIGHT)
	{
		auto search = pointLights.find(ID.id);
		if (search != pointLights.end())
			search->second = (PointLight)light;
	}
}
