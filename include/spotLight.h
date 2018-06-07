#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
//this is a derived class inheriting from Light
//you should use this class instead of the original base class Light
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "shader.h"
#include "light.h"

#include <string>


class SpotLight : public Light {
public:
	float inner_cutoff; //the angle specifies light's radius. 
	float outer_cutoff;	//some blur added to the edge of the light spot
	//default constructor
	//default color: white, ambient: 0.2, diffuse:0.8, specular:1.0, inner_cutoff:20, outer_cutoff:22
	SpotLight(glm::vec3 direction, glm::vec3 position, float inner, float outer) :
		Light(direction, position), inner_cutoff(inner), outer_cutoff(outer){}
	//direction and position are both required for a spot light
	SpotLight(glm::vec3 color, glm::vec3 direction, glm::vec3 position, glm::vec3 ambient, 
		glm::vec3 diffuse, glm::vec3 specular, float inner, float outer) : Light(color, direction, 
		position, ambient, diffuse, specular), inner_cutoff(inner), outer_cutoff(outer){} 

	//send all vectors to a specific shader with light's name
	void sendShader(Shader &shader, const std::string &name) const override;
};

#endif