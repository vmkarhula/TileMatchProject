#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace ErrorCallbacks {

	void GLFW_ErrorCallback(int error, const char* description);

	void GLAPIENTRY Callback_OpenGL_Error(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
}

namespace GLInfo {

	// Outputs the OpenGL version, device and vendor info 
	void PrintOpenGLInfo();
}

class MatchGame {

public:
	
	MatchGame();
	~MatchGame();

	bool Init();
	int Run();

private: 

	GLFWwindow* m_Window = nullptr;

	int m_windowWidth = 800;
	int m_windowHeight = 600;

};