#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
//this is a derived class of Light
//you should use this class instead of original base class
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "light.h"

#include <string>

class PointLight : public Light {
public:
	static const int att_table_size; //attenuation table size, set in souce file
	static const float att_table[];  //attenuation table, used to set attenuation according to range


	//default constructor
	//default color: white, ambient: 0.2, diffuse: 0.8, specular:1.0
	PointLight(glm::vec3 pos, float dis) : Light(glm::vec3(0), pos)
		{
			setAttenuation(dis);
		}

	//complete constructor
	PointLight(glm::vec3 col, glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float dis) :
		Light(col, glm::vec3(0), pos, amb, diff, spec)
		{
			setAttenuation(dis);
		}

	//send all vectors to a specific shader with light's name
	void sendShader(Shader &shader, const std::string &name) const override;
	//set all coefficients from range
	//you should call this function if you have changed range of this light
	void setAttenuation(float dis);

private:
	float constant;	//constant coefficient of attenuation	
	float linear;	//linear coefficient of attenuation
	float quadra;	//quadra coefficient of attenuation

	float range;	//this light's range. large value results in large covering area

};

#endif