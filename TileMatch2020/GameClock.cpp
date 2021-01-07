#include "GameClock.h"
#include "RenderUtil.h"

GameClock::GameClock(): m_clockDigitAtlas(LoadUtil::LoadTexture(".\\resource\\ph_digits.png"))
{
}

void GameClock::Render()
{
	
    int minutesTens = static_cast<int>(m_Minutes / 10);
    int minutesOnes = m_Minutes % 10;

    int secondsTens = static_cast<int>(m_Seconds / 10);
    int secondsOnes = m_Seconds % 10;

	float pos;

}

void GameClock::Update(float dt)
{
    if (!m_Paused) {

        m_TimeElapsed += dt;
        
        if (m_TimeElapsed > 1.0f) {

            m_Seconds++;
            m_TimeElapsed -= 1.0f;
        
            if (m_Seconds > 59) {
                
                m_Minutes++;
                m_Seconds -= 60;
            }

        }
    }
}

void GameClock::Pause()
{
    m_Paused = true;
}

void GameClock::Start()
{
    m_Paused = false;
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
