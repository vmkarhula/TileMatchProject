#include "SimpleShader.h"

// For reading the shader string
#include <sstream>
#include <fstream>
#include <iostream>

SimpleShader::SimpleShader(std::string vsPath, std::string fsPath): GL_ID(0)
{
	
	// Vertex shader read
	std::ifstream vsReader(vsPath);

	if (!vsReader) {

		std::cerr << "Error! Could not open vertex shader file " << vsPath << std::endl;
	}

	std::stringstream vsCodeStrStream;

	vsCodeStrStream << vsReader.rdbuf();

	vsReader.close();

	std::string vsCodeStr(vsCodeStrStream.str());

	if (vsCodeStr.empty())
		std::cerr << "Error reading the shader code string!" << std::endl;

	
	// Fragment shader read
	std::ifstream fsReader(fsPath);

	if (!fsReader) {

		std::cerr << "Error! Could not open fragment shader file " << fsPath << std::endl;
	}

	std::stringstream fsCodeStrStream;

	fsCodeStrStream << fsReader.rdbuf();

	fsReader.close();

	std::string fsCodeStr(fsCodeStrStream.str());

	if (fsCodeStr.empty())
		std::cerr << "Error reading the shader code string!" << std::endl;


	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	const char * vertexCStr = vsCodeStr.c_str();
	glShaderSource(vertex, 1, &vertexCStr, 0);
	glCompileShader(vertex);
	CheckCompilerErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentCStr = fsCodeStr.c_str();
	glShaderSource(fragment, 1, &fragmentCStr, 0);
	glCompileShader(fragment);
	CheckCompilerErrors(fragment, "FRAGMENT");

	// shader Program
	GL_ID = glCreateProgram();
	glAttachShader(GL_ID, vertex);
	glAttachShader(GL_ID, fragment);
	
	glLinkProgram(GL_ID);
	CheckCompilerErrors(GL_ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
}

SimpleShader::~SimpleShader()
{
	glDeleteProgram(GL_ID);
}

void SimpleShader::Bind()
{
	glUseProgram(GL_ID);
}

void SimpleShader::CheckCompilerErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	
	if (type != "PROGRAM") {

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {

			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR! Shader compilation failed: " << type << "\n" << infoLog << std::endl;
		}
	}

	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Error! Shader linking failed!: " << infoLog << std::endl;
		}
	}
}
