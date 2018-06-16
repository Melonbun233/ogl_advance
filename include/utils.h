#ifndef UTILS_H
#define UTILS_H
//this file contains all math and utility functions
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "shader.h"
#include "light.h"
#include "pointLight.h"
#include "dirLight.h"
#include "spotLight.h"
#include "config.h"

//initilize the window and glad
GLFWwindow* initWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, const std::string name);

#endif