#define STB_IMAGE_IMPLEMENTATION
#define PI 3.14159265
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "config.h" //include all necessary header files

using namespace std;
using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const string window_name = "Advanced OpenGL";

float delta_time = 0.0;
float current_frame = 0.0;
float last_frame = 0.0;

const extern float cube_vertices[];
const extern vec3 cube_pos[];

//setting up camera
Camera camera = Camera(vec3(0, 0, 6));
float MOUSE_X, MOUSE_Y;
GLboolean MOUSE_FIRST = true;
GLboolean MOUSE_VERTICAL_INVERSE = true;
GLboolean MOUSE_HORIZONTAL_INVERSE = false;

int main(int argc, char *argv[]){
	GLFWwindow *window = init(SCR_WIDTH, SCR_HEIGHT, window_name);
	if(window == NULL)
		return -1;

	if(MOUSE_VERTICAL_INVERSE)
		camera.setMouseVerticalInverse(true);
	if(MOUSE_HORIZONTAL_INVERSE)
		camera.setMouseHorizontalInverse(true);

	//configure paths
	const string curr_dir = string(argv[0]).substr(0, string(argv[0]).find_last_of('/'));
	const string vshader_path = curr_dir + "/../resources/shader/vshader.vs";
	const string fshader_path = curr_dir + "/../resources/shader/light.fs";
	const string nano_path = curr_dir + "/../resources/objects/nanosuit/nanosuit.obj";
	//slime/DirtSlime.fbx";

	Shader nano_shader(vshader_path, fshader_path);
	//--------------------------models---------------------------------------//
	Model nano(nano_path, nano_shader);

	mat4 nano_model;
	nano_model = translate(nano_model, vec3(0.0f, -1.75f, 0.0f));
	nano_model = scale(nano_model, vec3(0.3));

	//--------------------------configure light------------------------------//
	//direction/position, ambient, diffuse, specular, direction
	const int dirLightsNum = 1;
	const int pointLightsNum = 0;
	const int spotLightsNum = 0;
	DirLight dirLights[] = {
		DirLight(vec3(1.0, 1.0, 1.0), vec3(-0.2, -1.0, -0.3), vec3(0.8), vec3(2.0), vec3(1.0)),
		DirLight(vec3(1.0, 0.0, 0.0), vec3(0.2, 1.0, 0.3), vec3(0.1), vec3(0.8), vec3(1.0))
	};

	PointLight pointLights[] = {
		PointLight(vec3(3.0, 2.0, -1.0), 50.0f),
		PointLight(vec3(0.0, 0.0, -15.0), 50.0f)
	};

	SpotLight spotLights[] = {
		SpotLight(vec3(-1.0, -2.0, -2.0), vec3(1.0, 2.0, 2.0), 20.0, 22.0),
		SpotLight(vec3(-3.0, -2.0, -1.0), vec3(3.0, 2.0, -1.0), 20.0, 23.0)
	};
	spotLights[0].color = vec3(0.0, 1.0, 0.0);
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

		//update model, view, projection
		//drawing main object
		mat4 view, proj;
		view = camera.getView();
		proj = perspective(radians(camera.getFOV()), float(SCR_WIDTH/SCR_HEIGHT), 
			0.1f, 100.0f);

		//light
		sendDirLights(dirLights, dirLightsNum, nano.shader);

		nano.shader.setMat4("view", view);
		nano.shader.setMat4("proj", proj);
		nano.shader.setMat4("model",nano_model);
		nano.shader.setVec3("viewPos", camera.Position);

		//draw objects
		nano.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}