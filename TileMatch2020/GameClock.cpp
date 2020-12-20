#include "GameClock.h"

GameClock::GameClock()
{
}

void GameClock::Render()
{
	int minutesTens = static_cast<int>(m_Minutes / 10);
	int minutesOnes = m_Minutes % 10;

	int secondsTens = static_cast<int>(m_Seconds / 10);
	int secondsOnes = m_Seconds % 10;

	GLuint texMinutesTens = m_textureIDs[minutesTens];
	GLuint texMinutesOnes = m_textureIDs[minutesOnes];
	GLuint texSecondsTens = m_textureIDs[secondsTens];
	GLuint texSecondsOnes = m_textureIDs[secondsOnes];

	float pos;




}

void GameClock::Update(float dt)
{
}

void GameClock::Pause()
{
}

void GameClock::Start()
{
}

GLuint GameClock::CreateClockGeom()
{
   
        GLuint clockVB = 0;
        glGenBuffers(1, &clockVB);

        GLuint clockIB = 0;
        glGenBuffers(1, &clockIB);
            
        // Just X and Y coordinates, depth will always be 0
        float clockVertices[] = {

            // 10 minutes
            -1.0f, -1.0f,
            -0.55f, -1.0f,
            -1.0f, 1.0f,

            -1.0f, 1.0f,
            -0.55f,  -1.0f,
            -0.55f,  1.0f,

            // Minutes
            -0.55f, -1.0f,
            -0.1f, -1.0f,
            -0.55f,  1.0f,

            -0.55f, -1.0f,
            -0.1f, -1.0f,
            -0.1f,  1.0f,

            // The ":"
            -0.1f, -1.0f,
             0.1f, -1.0f,
            -0.1f,  1.0f,
            
            -0.1f,  1.0f,
             0.1f, -1.0f, 
             0.1f,  1.0f,

             // 10 seconds
             0.1f, -1.0f,
             0.55f, -1.0f,
             0.1f, 1.0f,
             
             0.1f, 1.0f,
             0.55f, -1.0f,
             0.55f, 1.0f,

             // Seconds
             0.55f, -1.0f,
             1.0f, -1.0f,
             0.55f, 1.0f,

             0.55f, 1.0f,
             1.0f, -1.0f,
             1.0f, 1.0f

        };

      


        return 0;
}
