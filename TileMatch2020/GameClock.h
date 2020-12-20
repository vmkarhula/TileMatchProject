#pragma once

#include <glad/glad.h>

class GameClock {

public:

	GameClock();

	void Render();
	void Update(float dt);

	void Pause();
	void Start();

private:

	GLuint CreateClockGeom();

	int m_Minutes = 0; 
	int m_Seconds = 0;

	float m_TimeElapsed = 0.0f; 
	bool m_Paused = true;

	GLuint m_textureIDs[10]{};
};