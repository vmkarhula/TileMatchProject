#pragma once

#include <string>

#include "glad/glad.h"

class SimpleShader {

public:

	unsigned int GL_ID;

	SimpleShader(std::string vsPath, std::string fsPath);
	~SimpleShader();

	// 
	void Bind();

	// TODO: Set Uniform stuff

private:

	void CheckCompilerErrors(GLuint shader, std::string type);

	// The OpenGL Handle
	


};