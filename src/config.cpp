#include "../include/config.h"
//this file contains all config functions 

float MOUSE_X, MOUSE_Y;
bool MOUSE_FIRST = true;

GLFWwindow* initWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, const string name){
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
	glEnable(GL_STENCIL_TEST);
	glDepthFunc(GL_LESS);

	return window;
}

//process user input
void processInput(GLFWwindow *window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->processKeypad(FORWARD, delta_time);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->processKeypad(BACKWARD, delta_time);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->processKeypad(LEFT, delta_time);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->processKeypad(RIGHT, delta_time);
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->processKeypad(UP, delta_time);
}

//this callback function is called whenever the window size is changed
void framebuffer_size_callback(GLFWwindow *window,int width, int height){
	glViewport(0, 0, width, height);
}

//call back function whenever mouse is moved
void mouse_callback(GLFWwindow *window,double x, double y){
	if(MOUSE_FIRST){
		MOUSE_FIRST = false;
		MOUSE_X = x;
		MOUSE_Y = y;
	}
	float x_offset = x - MOUSE_X;
	float y_offset = y - MOUSE_Y;
	MOUSE_X = x;
	MOUSE_Y = y;
	camera->processMouseMovement(x_offset, y_offset);
}

//call back function whenever mouse is scolled
//y is the value that mouse scrolled
void scroll_callback(GLFWwindow *window, double x, double y){
	camera->processMouseScroll(y);
}