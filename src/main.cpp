#define STB_IMAGE_IMPLEMENTATION
#define PI 3.14159265
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "config.h" //include all necessary header files

using namespace std;
using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const string window_name = "Advanced OpenGL";

float delta_time = 0.0;
float current_frame = 0.0;
float last_frame = 0.0;

//setting up scene and camera
//init and config scene, set the camera at (0, 0, 6)
Scene scene(vec3(0, 0, 6), SCR_WIDTH, SCR_HEIGHT);
Camera *camera;
float MOUSE_X, MOUSE_Y;
GLboolean MOUSE_FIRST = true;
GLboolean MOUSE_VERTICAL_INVERSE = true;
GLboolean MOUSE_HORIZONTAL_INVERSE = false;

int main(int argc, char *argv[]){
	GLFWwindow *window = initWindow(SCR_WIDTH, SCR_HEIGHT, window_name);
	if(window == NULL)
		return -1;

	camera = scene.getCamera();
	if(MOUSE_VERTICAL_INVERSE)
		camera->setMouseVerticalInverse(true);
	if(MOUSE_HORIZONTAL_INVERSE)
		camera->setMouseHorizontalInverse(true);

	//configure paths
	const string curr_dir = string(argv[0]).substr(0, string(argv[0]).find_last_of('/'));
	const string vshader_path = curr_dir + "/../resources/shader/vshader.vs";
	const string fshader_path = curr_dir + "/../resources/shader/light.fs";
	const string nano_path = curr_dir + "/../resources/objects/nanosuit/nanosuit.obj";
	//slime/DirtSlime.fbx";
	//nanosuit model
	SceneID nano_id = scene.addModel(nano_path, vshader_path, fshader_path);
	mat4 nano_model;
	nano_model = translate(nano_model, vec3(0.0f, -1.75f, 0.0f));
	nano_model = scale(nano_model, vec3(0.3));
	scene.setModelPos(nano_id, nano_model);

	//ground model
	Material ground_mat;
	ground_mat.ambient = vec3(1.0f);
	ground_mat.diffuse = vec3(1.0f);
	vector<string> ground_tex;
	ground_tex.push_back("");
	ground_tex.push_back("../resources/textures/container.png");
	ground_tex.push_back("");
	SceneID ground = scene.addPlane(vshader_path, fshader_path, ground_mat, ground_tex);
	scene.setModelPos(ground, mat4(0));

	//test
	Model *test = scene.getModel(nano_id);
	cout << test->meshes[0] << endl;

	//--------------------------configure light------------------------------//
	//direction/position, ambient, diffuse, specular, direction
	//white
	SceneID dir_white = scene.addDirLight(vec3(1.0, 1.0, 1.0), vec3(-0.2, -1.0, -0.3),
		vec3(0.1), vec3(2.0), vec3(1.0));

	//-----------------------resndering loop---------------------------------//
	while (!glfwWindowShouldClose(window)){
		processInput(window);
		//update frame timer
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		//clear last frame
		glClearColor(0.25, 0.25, 0.25, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw objects
		scene.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}