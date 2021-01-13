#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Deck.h"
#include "RenderUtil.h"
#include "GameClock.h"

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


namespace InputCallbacks {

	static void I_MouseButtonForwarder(GLFWwindow* window, int button, int action, int mods);
	static void I_MousePositionForwarder(GLFWwindow* window, double xpos, double ypos);

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
	
	void I_MouseButton(GLFWwindow* window, int button, int action, int mods);
	void I_MousePosition(GLFWwindow* window, double xpos, double ypos);

private: 
	
	// Represents a click with target area and normalized coordinates in it 
	// (0.0, 0.0) for top left 
	struct ClickData {

		enum class Target{UNKOWN, MENU, PLAYAREA, MISS};

		Target target;

		double x;
		double y; 

	};

	ScreenRect CalculateGameArea(int screenWidth, int screenHeight);

	void RenderClock();

	ClickData ResolveClick(double mouse_x, double mouse_y);

	GLFWwindow* m_Window = nullptr;

	Deck* m_Deck = nullptr;
	GameClock* m_GameClock = nullptr;

	int m_windowWidth = 1280;
	int m_windowHeight = 720;

	double m_MouseX = 0.0;
	double m_MouseY = 0.0;

	double m_PrevTick = 0.0;
	double m_TimeElapsed = 0.0;

	ScreenRect m_PlayAreaRect = { 50, 50, m_windowWidth - 300, m_windowHeight - 100 };
	ScreenRect m_TimerRect{ m_windowWidth - 200, m_windowHeight - 100, 150, 50 };

};