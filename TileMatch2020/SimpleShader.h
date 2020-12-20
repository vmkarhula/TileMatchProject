#pragma once

#include <string>
#include <unordered_map>

#include "glad/glad.h"

class SimpleShader {

public:
	
	// The OpenGL Handle
	unsigned int GL_ID;

	SimpleShader(std::string vsPath, std::string fsPath);
	~SimpleShader();

	GLuint FindUniformLoc(std::string uniformName);

	// 
	void Bind();

	// TODO: Set Uniform stuff

private:

	void CheckCompilerErrors(GLuint shader, std::string type);

	std::unordered_map<std::string, GLuint> m_ShaderCache;


};