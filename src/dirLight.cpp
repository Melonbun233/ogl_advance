#include "../include/dirLight.h"

using namespace glm;
using namespace std;

void DirLight::sendShader(Shader &shader, const string &name) const
{

	string dir(name);
	string amb(name);
	string diff(name);
	string spec(name);

	shader.setVec3(dir.append(".direction"), direction);
	shader.setVec3(amb.append(".ambient"), ambient * color);
	shader.setVec3(diff.append(".diffuse"), diffuse * color);
	shader.setVec3(spec.append(".specular"), specular * color);
}