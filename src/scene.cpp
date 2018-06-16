#include "scene.h"

using namespace glm;
using namespace std;

void Scene::setPosition(SceneID id, mat4 pos)
{
	if(id.type == MODEL)
	{
		//searching model
		auto search = models.find(id.id);
		if(search != models.end())
		{
			Model model = search->second;
			mat4 view, proj;
			view = camera.getView();
			if (perspec)
				proj = perspective(radians(camera.getFOV()), float(scrWidth)/float(scrHeight), 0.1f, 100.0f);
			else
				proj = ortho(0.0f, float(scrWidth), 0.0f, float(scrHeight), 0.1f, 100.0f);
			//set model's shader
			setShader(model.shader, pos, view, proj);
		}
	}
}

void Scene::setShader(Shader &shader, mat4 model, mat4 view, mat4 proj)
{
	shader.use();
	shader.setMat4("view", view);
	shader.setMat4("proj", proj);
	shader.setMat4("model", model);
	shader.setVec3("viewPos", camera.Position);
}

void Scene::render()
{
	sendLights();
	for (auto it = models.begin(); it != models.end(); it++)
	{
		it->second.render();
	}
}

void Scene::sendLights()
{
	for(auto it = models.begin(); it != models.end(); it++) //iterating through all models
	{
		sendPointLights(it->second.shader);
		sendDirLights(it->second.shader);
		sendSpotLights(it->second.shader);
	}
}

void Scene::sendPointLights(Shader &shader)
{
	int i;
	shader.use();
	shader.setInt("POINT_LIGHTS_NUM", pointLights.size());
	for(auto it = pointLights.begin(); it != pointLights.end(); it++)
	{
		it->second.sendShader(shader, "pointLights[" + to_string(i++) + "]");
	}
}

void Scene::sendDirLights(Shader &shader)
{
	int i;
	shader.use();
	shader.setInt("DIR_LIGHTS_NUM", dirLights.size());
	for(auto it = dirLights.begin(); it != dirLights.end(); it++)
	{
		it->second.sendShader(shader, "dirLights[" + to_string(i++) + "]");
	}
}

void Scene::sendSpotLights(Shader &shader)
{
	int i;
	shader.use();
	shader.setInt("SPOT_LIGHTS_NUM", spotLights.size());
	for(auto it = spotLights.begin(); it != spotLights.end(); it++)
	{
		it->second.sendShader(shader, "spotLights[" + to_string(i++) + "]");
	}
}

SceneID Scene::addModel(const string path, const string vshader, const string fshader)
{
	Shader shader(vshader, fshader);
	Model model(path, shader);
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

SceneID Scene::addSpotLight(vec3 color, vec3 direction, vec3 position, vec3 ambient, 
	vec3 diffuse, vec3 specular, float inner, float outer)
{
	SpotLight light(color, direction, position, ambient, diffuse, specular, inner, outer);
	unsigned int id = count ++;
	spotLights.insert({id, light});
	return SceneID(id, SPOT_LIGHT);
}

SceneID Scene::addSpotLight(SpotLight &light)
{
	unsigned int id = count ++;
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

SceneID Scene::addDirLight(vec3 color, vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular)
{
	DirLight light(color, direction, ambient, diffuse, specular);
	unsigned int id = count ++;
	dirLights.insert({id, light});
	return SceneID(id, DIR_LIGHT);
}

SceneID Scene::addDirLight(DirLight &light)
{
	unsigned int id = count ++;
	dirLights.insert({id, light});
	return SceneID(id, DIR_LIGHT);
}

SceneID Scene::addPointLight(vec3 position, float distance)
{
	PointLight light(position, distance);
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

SceneID Scene::addPointLight(PointLight &light)
{
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

void Scene::removeModel(SceneID ID)
{
	if (ID.type == MODEL)
	{
		auto search = models.find(ID.id);
		if (search != models.end())
			models.erase(search);
	}
}

SpotLight* Scene::getSpotLight(SceneID ID)
{
	if (ID.type == SPOT_LIGHT)
	{
		auto search = spotLights.find(ID.id);
		if (search != spotLights.end())
			return &(search->second);
	}
	return NULL;
}

DirLight* Scene::getDirLight(SceneID ID)
{
	if(ID.type == DIR_LIGHT)
	{
		auto search = dirLights.find(ID.id);
		if (search != dirLights.end())
			return &(search->second);
	}
	return NULL;
}

PointLight* Scene::getPointLight(SceneID ID)
{
	if(ID.type == POINT_LIGHT)
	{
		auto search = pointLights.find(ID.id);
		if(search != pointLights.end())
			return &(search->second);
	}
	return NULL;
}

Model* Scene::getModel(SceneID ID)
{
	if(ID.type == MODEL)
	{
		auto search = models.find(ID.id);
		if(search != models.end())
			return &(search->second);
	}
	return NULL;
}

Camera* Scene::getCamera()
{
	return &camera;
}
