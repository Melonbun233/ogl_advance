#include "../include/pointLight.h"

using namespace glm;
using namespace std;

const int PointLight::att_table_size = 12;

const float PointLight::att_table[] = {
	7.0, 	1.0, 	0.7, 	1.8,
	13.0, 	1.0, 	0.35, 	0.44,
	20.0, 	1.0, 	0.22, 	0.20,
	32.0, 	1.0, 	0.14, 	0.07,
	50.0, 	1.0, 	0.09, 	0.032,
	65.0, 	1.0, 	0.07, 	0.017,
	100.0, 	1.0, 	0.045, 	0.0075,
	160.0, 	1.0, 	0.027, 	0.0028,
	200.0, 	1.0, 	0.022, 	0.0019,
	325.0, 	1.0, 	0.014, 	0.0007,
	600.0, 	1.0, 	0.007, 	0.0002,
	3250.0, 1.0, 	0.0014, 0.000007
};

//get attenuation values
void PointLight::setAttenuation(float _range){
	range = _range;
	for (int i = 0; i < att_table_size; i ++){
		if(_range <= att_table[i * 4]){
			constant = att_table[i * 4 + 1];
			linear = att_table[i * 4 + 2];
			quadra = att_table[i * 4 + 3];
			return;
		}
	}
	//range larger than the largest distance on the table
	constant = att_table[(att_table_size - 1) * 4 + 1];
	linear = att_table[(att_table_size - 1) * 4 + 2];
	quadra = att_table[(att_table_size - 1) * 4 + 3];
}

void PointLight::sendShader(Shader &shader, const string &name) const
{
	string pos(name);
	string amb(name);
	string diff(name);
	string spec(name);
	string cons(name);
	string lin(name);
	string quad(name);

	shader.setVec3(pos.append(".position"), position);
	shader.setVec3(amb.append(".ambient"), ambient * color);
	shader.setVec3(diff.append(".diffuse"), diffuse * color);
	shader.setVec3(spec.append(".specular"), specular * color);
	shader.setFloat(cons.append(".constant"), constant);
	shader.setFloat(lin.append(".linear"), linear);
	shader.setFloat(quad.append(".quadra"), quadra);

}