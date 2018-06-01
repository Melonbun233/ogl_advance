#ifndef DIR_LIGHT_H
#define DIR_LIGHT_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "light.h"

#include <string>


//this is a derived class from light base class.
//you should use this class instead of Light

class DirLight : public Light {	//inherits from Light
public:
	//default constructor
	//default color: white, ambient:0.2, diffuse:0.8, specular:1.0
	DirLight(glm::vec3 dir) : Light(dir, glm::vec3(0)){}

	//position is set to zero in this constructor because directional light 
	//desn't have a postion direction vector is pointing from 
	//the light source to the fragment
	//complete constructor
	DirLight(glm::vec3 col, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) :
	Light(col, dir, glm::vec3(0.0), amb, diff, spec){}

	//send all vectors to a specific shader with light's name
	void sendShader(Shader &shader, const std::string &name) const override;
};


#endif