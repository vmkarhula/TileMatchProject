#pragma once

#include <glad/glad.h>
#include "SimpleShader.h"

class GameClock {

public:

	GameClock();

	void Render();
	void Update(float reading, float dt);

	void Pause();
	void Start();

private:

	struct Coord2D {

		float x, y;
	};

	GLuint CreateClockGeom();
	void DrawQuad(Coord2D topLeft, Coord2D bottomRight, Coord2D atlasTopLeft, Coord2D atlasBottomRight);

	int m_Minutes = 0; 
	int m_Seconds = 0;

	float m_TimeElapsed = 0.0f; 
	bool m_Paused = true;
	
	GLuint m_clockVAO = 0;
	GLuint m_clockDigitAtlas = 0;
	SimpleShader m_clockDigitShader;

};