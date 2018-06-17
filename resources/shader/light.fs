#version 330 core
#define LIGHTS_LIMIT 10
#define TEXTURE_LIMIT 5

struct Material{
	sampler2D tex_ambient[TEXTURE_LIMIT];
	sampler2D tex_diffuse[TEXTURE_LIMIT];
	sampler2D tex_specular[TEXTURE_LIMIT];
	int amb_num;
	int diff_num;
	int spec_num;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadra;
};

struct SpotLight {
	vec3 direction;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float inner_cutoff;	
	float outer_cutoff;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform int DIR_LIGHTS_NUM;
uniform int POINT_LIGHTS_NUM;
uniform int SPOT_LIGHTS_NUM;

uniform DirLight dirLights[LIGHTS_LIMIT]; 
uniform PointLight pointLights[LIGHTS_LIMIT];
uniform SpotLight spotLights[LIGHTS_LIMIT];

uniform Material material;
uniform vec3 viewPos;

//functions to calculate ambient, diffuse and specular
vec3 calcAmbient(vec3 light_amb);
vec3 calcDiffuse(vec3 light_diff, vec3 normal, vec3 lightDir);
vec3 calcSpecular(vec3 light_spec, vec3 normal, vec3 lightDir, vec3 viewDir);

//functions to calculate different light type
vec3 processDirLights(vec3 normal, vec3 viewDir);
vec3 processPointLights(vec3 normal, vec3 viewDir);
vec3 processSpotLights(vec3 normal, vec3 viewDir);

void main()
{
	//light properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result;

	result += processDirLights(norm, viewDir);
	result += processPointLights(norm, viewDir);
	result += processSpotLights(norm, viewDir);
	if(result == vec3(0))	//no light in this shader, add ambient light manually
	{
		result += calcAmbient(vec3(0.2));
	}

	FragColor = vec4(result, 1.0);

}

vec3 processDirLights(vec3 normal, vec3 viewDir)
{
	vec3 lightDir, ambient, diffuse, specular;
	for (int i = 0; i < DIR_LIGHTS_NUM; i ++)
	{	
		lightDir = normalize(-dirLights[i].direction);
		ambient += calcAmbient(dirLights[i].ambient);
		diffuse += calcDiffuse(dirLights[i].diffuse, normal, lightDir);
		specular += calcSpecular(dirLights[i].specular, normal, lightDir, viewDir);
	}
	return (ambient + diffuse + specular);
}

vec3 processPointLights(vec3 normal, vec3 viewDir)
{
	vec3 lightDir, ambient, diffuse, specular;
	for (int i = 0; i < POINT_LIGHTS_NUM; i ++)
	{
		lightDir = normalize(pointLights[i].position - FragPos);
		//calculate attenuation
		float dis = length(pointLights[i].position - FragPos);
		float attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear*dis + 
			pointLights[i].quadra*(dis*dis));

		ambient += calcAmbient(pointLights[i].ambient) * attenuation; 
		diffuse += calcDiffuse(pointLights[i].diffuse, normal, lightDir) * attenuation;
		specular += calcSpecular(pointLights[i].specular, normal, lightDir, viewDir) * attenuation;
	}
	
	return (ambient + diffuse + specular);
}

vec3 processSpotLights(vec3 normal, vec3 viewDir)
{
	vec3 lightDir, ambient, diffuse, specular;
	for (int i = 0; i < SPOT_LIGHTS_NUM; i ++)
	{
		lightDir = normalize(spotLights[i].position - FragPos);
		//calculate theta, angle between light direction and frag direction
		float theta = dot(lightDir, normalize(-spotLights[i].direction));
		float epsilon = spotLights[i].inner_cutoff - spotLights[i].outer_cutoff;
		float intensity = clamp((theta - spotLights[i].outer_cutoff) / epsilon, 0.0, 1.0);

		//do light calculation
		ambient += calcAmbient(spotLights[i].ambient);
		diffuse += calcDiffuse(spotLights[i].diffuse, normal, lightDir) * intensity;
		specular += calcSpecular(spotLights[i].specular, normal, lightDir, viewDir) * intensity;
	}

	return (ambient + diffuse + specular);
}

vec3 calcAmbient(vec3 light_amb)
{
	vec3 tex; 
	if (material.amb_num == 0)	//no ambient map, use material's own ambient color
		tex = material.ambient;
	else
	{
		for (int i = 0; i < material.amb_num; i ++)
			tex += vec3(texture(material.tex_ambient[i], TexCoords));
	}
	
	return light_amb * tex;
}

vec3 calcDiffuse(vec3 light_diff, vec3 normal, vec3 lightDir)
{
	vec3 tex;
	float diff = max(dot(normal, lightDir), 0.0);

	if (material.diff_num == 0) //no diffuse map, use material's own diffuse color
		tex = material.diffuse;
	else 
	{
		for (int i = 0; i < material.diff_num; i ++)
			tex += vec3(texture(material.tex_diffuse[i], TexCoords));
	}
	return light_diff * diff * tex;
}

vec3 calcSpecular(vec3 light_spec, vec3 normal, vec3 lightDir, vec3 viewDir)
{
	vec3 tex;
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	if (material.spec_num == 0) //no specular map, use material's own specular color
		tex = material.specular;
	else 
	{
		for (int i = 0; i < material.spec_num; i ++)
			tex += vec3(texture(material.tex_specular[i], TexCoords));
	}

	return light_spec * spec * tex;
}






