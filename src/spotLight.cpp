#include "../include/spotLight.h"

using namespace glm;
using namespace std;

void SpotLight::sendShader(Shader &shader, const string &name) const
{
	string dir(name);
	string pos(name);
	string amb(name);
	string diff(name);
	string spec(name);
	string inner(name);
	string outer(name);

	shader.setVec3(dir.append(".direction"), direction);
	shader.setVec3(pos.append(".position"), position);
	shader.setVec3(amb.append(".ambient"), ambient * color);
	shader.setVec3(diff.append(".diffuse"), diffuse * color);
	shader.setVec3(spec.append(".specular"), specular * color);
	shader.setFloat(inner.append(".inner_cutoff"), cos(radians(inner_cutoff)));
	shader.setFloat(outer.append(".outer_cutoff"), cos(radians(outer_cutoff)));
}