// this is the shader source code for the shader class
#include "../include/shader.h"

//use this shader program
void Shader::use(){
	glUseProgram(ID);
}


//constructor
Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
	vertex = vertexPath;
	fragment = fragmentPath;
	setup(vertex, fragment);
}

void Shader::setup(const std::string &vertexPath, const std::string &fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//check ifstream objects can throw exception
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//read file's buffer contentes into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		//cout << vertexCode << endl;
		fragmentCode = fShaderStream.str();
		//cout << fragmentCode << endl;
	} catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//compile shader
	int vertex, fragment;

	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkShaderSuccess(vertex, "vertex");
	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkShaderSuccess(fragment, "fragment");

	//shader programs
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkLinkSuccess(ID);

	//delete the shaders as they're linked into the shader program
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
// check whether shader is compiled succesfully
void Shader::checkShaderSuccess(unsigned int shader, const std::string &type){
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << type << " shader compilation error\n" << infoLog << std::endl;
		return;
	}
}
// check whether shader program is succesfully linked
void Shader::checkLinkSuccess(unsigned int ID){
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Shader Program Linking Error\n" << infoLog << std::endl;
		return;
	}
}