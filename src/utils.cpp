#include "../include/utils.h"
using namespace std;
//this file contains all math and other utility functions

GLFWwindow* init(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, const string name){
	//initiate glfw and window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to load glad" << endl;
		return NULL;
	}

	glEnable(GL_DEPTH_TEST);
	return window;
}

void sendPointLights(PointLight lights[], int light_num, Shader &shader)
{
	shader.use();
	shader.setInt("POINT_LIGHTS_NUM", light_num);
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "pointLights[" + to_string(i) + "]");
	}
}

void sendDirLights(DirLight lights[], int light_num, Shader &shader)
{
	shader.use();
	shader.setInt("DIR_LIGHTS_NUM", light_num);
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "dirLights[" + to_string(i) + "]");
	}
}

void sendSpotLights(SpotLight lights[], int light_num, Shader &shader)
{
	shader.use();
	shader.setInt("SPOT_LIGHTS_NUM", light_num);
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "spotLights[" + to_string(i) + "]");
	}
}