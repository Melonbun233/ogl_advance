#define STB_IMAGE_IMPLEMENTATION
#define PI 3.14159265
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "config.h" //include all necessary header files

using namespace std;
using namespace glm;

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;
const string window_name = "Advanced OpenGL";

float delta_time = 0.0;
float current_frame = 0.0;
float last_frame = 0.0;

//setting up scene and camera
//init and config scene, set the camera at (0, 0, 6)
Camera *camera;
GLboolean MOUSE_VERTICAL_INVERSE = true;
GLboolean MOUSE_HORIZONTAL_INVERSE = false;

int main(int argc, char *argv[]){

	GLFWwindow *window = initWindow(SCR_WIDTH, SCR_HEIGHT, window_name);
	if(window == NULL)
		return -1;

	//configure paths
	const string curr_dir = string(argv[0]).substr(0, string(argv[0]).find_last_of('/'));
	const string nano_path = curr_dir + "/../resources/objects/nanosuit/nanosuit.obj";
	const string tex_floor = curr_dir + "/../resources/textures/floor.jpg";
	const string tex_stone = curr_dir + "/../resources/textures/stone.jpg";
	const string tex_grass = curr_dir + "/../resources/textures/grass.png";
	const string tex_window = curr_dir + "/../resources/textures/transparent_window.png";

	Scene scene(curr_dir, vec3(0, 1, 3), SCR_WIDTH, SCR_HEIGHT);
	camera = scene.getCamera();
	if(MOUSE_VERTICAL_INVERSE)
		camera->setMouseVerticalInverse(true);
	if(MOUSE_HORIZONTAL_INVERSE)
		camera->setMouseHorizontalInverse(true);

	//-------------------------configure model-------------------------------//
	//grass material
	Material mat_grass(vec3(0), vec3(0), vec3(0), 8.0f);
	vector<string> grass_tex = {tex_grass, tex_grass, tex_grass};
	SceneID grasses[5];
	for (int i = 0; i < 5; i ++)
	{
		grasses[i] = scene.addPlane(mat_grass, grass_tex);
		scene.setModelPos(grasses[i], vec3(-3.0f + i, 0.5f, -2.0f + i));
		scene.setModelRotate(grasses[i], 90.0f, vec3(1.0f, 0.0f, 0.0f));
	}
	//ground model
	Material ground_mat(vec3(0), vec3(0), vec3(0), 8.0f);
	vector<string> ground_tex = {tex_floor, tex_floor, tex_floor};
	SceneID ground = scene.addPlane(ground_mat, ground_tex);
	scene.setModelScale(ground, vec3(10.0f));
 
 	//two cubes
	Material cube_mat(vec3(0), vec3(0), vec3(0), 16.0f);
	vector<string> cube_tex = {tex_stone, tex_stone, tex_stone};
	SceneID cube_1 = scene.addCube(cube_mat, cube_tex);
	scene.setModelPos(cube_1, vec3(0.0, 0.5001, 0.0));

	SceneID cube_2 = scene.addCube(cube_mat, cube_tex);
	scene.setModelPos(cube_2, vec3(-1.5, 0.5001, -3.0));

	//window
	Material window_mat(vec3(0), vec3(0), vec3(0), 32.0f);
	vector<string> window_tex = {tex_window, tex_window, tex_window};
	SceneID win = scene.addPlane(window_mat, window_tex);
	scene.setModelRotate(win, 90.0f, vec3(1.0f, 0.0, 0.0f));
	scene.setModelPos(win, vec3(0.0f, 3.0f, 3.0f));
	scene.setModelScale(win, vec3(3.0f));

	//--------------------------configure light------------------------------//
	//white
	SceneID dir_white = scene.addDirLight(vec3(1.0, 1.0, 1.0), vec3(-0.2, -1.0, -0.3),
		vec3(0.2), vec3(0.5), vec3(0.5));

	//-----------------------resndering loop---------------------------------//
	while (!glfwWindowShouldClose(window)){
		processInput(window);
		//update frame timer
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		//clear last frame
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//draw objects
		scene.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}