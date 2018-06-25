#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

class Shader{

public: 
	//constructor that builds and reads the shader
	Shader(const std::string &vertexPath, const std::string &fragmentPath);

	Shader() = default;

	void setup(const std::string&, const std::string&);

	//shader program ID
	int ID;

	//this function should be called before each rendering
	void use();

	//set a bool uniform in the shader
	void setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	//set a integer uniform in the shader
	void setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	//set a float uniform in the shader
	void setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	//set a mat4 unifrom in the shader
	void setMat4(const std::string &name, glm::mat4 value) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value_ptr(value));
	}
	//set a vec3 uniform in the shader
	void setVec3(const std::string &name, glm::vec3 value) const {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value_ptr(value));
	}
	//set a vec4 uniform in the shader
	void setVec4(const std::string &name, glm::vec4 value) const {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, value_ptr(value));
	}


private:
	std::string vertex, fragment;
	// check whether shader is compiled succesfully
	void checkShaderSuccess(unsigned int shader, const std::string &type);
	// check whether shader program is succesfully linked
	void checkLinkSuccess(unsigned int ID);

};


#endif