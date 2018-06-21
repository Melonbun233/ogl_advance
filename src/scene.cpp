#include "scene.h"

using namespace glm;
using namespace std;

void Scene::setModelPos(SceneID id, mat4 pos)
{
	if(id.type == MODEL)
	{
		//searching model
		auto search = models.find(id.id);
		if(search != models.end())
		{
			Model model = search->second;
			model.shader.use();
			model.shader.setMat4("model", pos);
			return;
		}
		cout << "Model ID not found" << endl;
		return;
	}
	cout << "Invalid ID: not MODEL";
}

void Scene::setShader(Model &obj, mat4 view, mat4 proj)
{
	obj.shader.use();
	obj.shader.setMat4("view", view);
	obj.shader.setMat4("proj", proj);
	obj.shader.setVec3("viewPos", camera.Position);
}

void Scene::render()
{
	for (auto it = models.begin(); it != models.end(); it++)
	{
		sendLights(it->second);
		//updating view and projection matrices
		mat4 view, proj;
		view = camera.getView();
		proj = getProjMat();
		setShader(it->second, view, proj);
		it->second.render();
	}
}

void Scene::sendLights(Model &model)
{
	int i;
	model.shader.use();
	model.shader.setInt("POINT_LIGHTS_NUM", pointLights.size());
	model.shader.setInt("DIR_LIGHTS_NUM", dirLights.size());
	model.shader.setInt("SPOT_LIGHTS_NUM", spotLights.size());

	for(auto it = pointLights.begin(); it != pointLights.end(); it++)
	{
		it->second.sendShader(model.shader, "pointLights[" + to_string(i++) + "]");
	}

	i = 0;
	for(auto it = dirLights.begin(); it != dirLights.end(); it++)
	{
		it->second.sendShader(model.shader, "dirLights[" + to_string(i++) + "]");
	}

	i = 0;
	for(auto it = spotLights.begin(); it != spotLights.end(); it++)
	{
		it->second.sendShader(model.shader, "spotLights[" + to_string(i++) + "]");
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

SceneID Scene::addPlane(const string vshader, const string fshader, Material &mat,
	vector<string> &tex_path)
{
	Shader shader(vshader, fshader);
	Model model = loadModel(shader, square_vertices, square_indices, square_vertices_num, 
		square_indices_num, mat, tex_path);
	//assign id
	unsigned int id = count ++;
	models.insert({id, model});
	return SceneID(id, MODEL);
}

SceneID Scene::addCube(const string vshader, const string fshader, Material &mat,
	vector<string> &tex_path)
{
	Shader shader(vshader, fshader);
	Model model = loadModel(shader, cube_vertices, cube_indices, cube_vertices_num,
		cube_indices_num, mat, tex_path);
	//assign id
	unsigned int id = count ++;
	models.insert({id, model});
	return SceneID(id, MODEL);
}

Model Scene::loadModel(Shader &shader, const float vertices[], const unsigned int indices[], 
	const int vertex_num, const int index_num, Material &mat, vector<string> &tex_path)
{
	//load model
	vector<vec3> positions, normals;
	vector<vec2> coords;
	vector<unsigned int> index;

	for(int i = 0; i < vertex_num; i ++)
	{
		positions.push_back(vec3(vertices[i*8], vertices[1+i*8], vertices[2+i*8]));
		coords.push_back(vec2(vertices[3+i*8], vertices[4+i*8]));
		normals.push_back(vec3(vertices[5+i*8], vertices[6+i*8], vertices[7+i*8]));
	}

	for(int i = 0; i < index_num; i ++)
	{
		index.push_back(indices[i]);
	}

	return Model(shader, positions, normals, index, coords, mat, tex_path);
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
		{
			spotLights.erase(search);
			return;
		}
		cout << "Spot Light ID not found" << endl;
		return;
	} 
	cout << "Invalid ID: not SpotLight" << endl;
}

void Scene::removeDirLight(SceneID ID)
{
	if (ID.type == DIR_LIGHT)
	{
		auto search = dirLights.find(ID.id);
		if (search != dirLights.end())
		{
			dirLights.erase(search);
			return;
		}
		cout << "Directional Light ID not found" << endl;
		return;
	}
	cout << "Invalid ID: not DirLight" << endl;
}

void Scene::removePointLight(SceneID ID)
{
	if (ID.type == POINT_LIGHT)
	{
		auto search = pointLights.find(ID.id);
		if (search != pointLights.end())
		{
			pointLights.erase(search);
			return;
		}
		cout << "Point Light ID not found" << endl;
		return;
	}
	cout << "Invalid ID: not PointLight" << endl;
}

void Scene::removeModel(SceneID ID)
{
	if (ID.type == MODEL)
	{
		auto search = models.find(ID.id);
		if (search != models.end())
		{
			models.erase(search);
			return;
		}
		cout << "Model ID not found" << endl;
		return;
	}
	cout << "Invalid ID: not MODEL" << endl;
}

SpotLight* Scene::getSpotLight(SceneID ID)
{
	if (ID.type == SPOT_LIGHT)
	{
		auto search = spotLights.find(ID.id);
		if (search != spotLights.end())
			return &(search->second);
		cout << "Spot Light ID not found" << endl;
		return NULL;
	}
	cout << "Invalid ID: not SpotLight" << endl;
	return NULL;
}

DirLight* Scene::getDirLight(SceneID ID)
{
	if(ID.type == DIR_LIGHT)
	{
		auto search = dirLights.find(ID.id);
		if (search != dirLights.end())
			return &(search->second);
		cout << "Directional Light ID not found" << endl;
		return NULL;
	}
	cout << "Invalid ID: not DirLight" << endl;
	return NULL;
}

PointLight* Scene::getPointLight(SceneID ID)
{
	if(ID.type == POINT_LIGHT)
	{
		auto search = pointLights.find(ID.id);
		if(search != pointLights.end())
			return &(search->second);
		cout << "Point Light ID not found" << endl;
		return NULL;
	}
	cout << "Invalid ID: not Point Light";
	return NULL;
}

Model* Scene::getModel(SceneID ID)
{
	if(ID.type == MODEL)
	{
		auto search = models.find(ID.id);
		if(search != models.end())
			return &(search->second);
		cout << "Model ID not found" << endl;
		return NULL;
	}
	cout << "Invalid ID: not Model" << endl;
	return NULL;
}

Camera* Scene::getCamera()
{
	return &camera;
}

mat4 Scene::getProjMat()
{
	mat4 proj;
	if (perspec)
		proj = perspective(radians(camera.getFOV()), float(scrWidth)/float(scrHeight),
			0.1f, 100.0f);
	else
		proj = ortho(0.0f, float(scrWidth), 0.0f, float(scrHeight), 0.1f, 100.0f);

	return proj;
}
