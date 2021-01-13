#include "GameClock.h"
#include "RenderUtil.h"

#include "glm/glm.hpp"

GameClock::GameClock() :
    m_clockVAO(CreateClockGeom()),
    m_clockDigitAtlas(LoadUtil::LoadTexture(".\\resource\\ph_digits.png")),
    m_clockDigitShader(".\\shader\\clockdigit.vs.glsl", ".\\shader\\clockdigit.fs.glsl")
{
    m_clockDigitShader.FindUniformLoc("atlasCoordinates");
     
}

void GameClock::Render()
{
	
    int minutesTens = static_cast<int>(m_TimeElapsed / 600);
    int minutesOnes = static_cast<int>(m_TimeElapsed / 60);

    int secondsTens = static_cast<int>(m_TimeElapsed / 10) % 6;
    int secondsOnes = static_cast<int>(m_TimeElapsed) % 10;
    
    glUseProgram(m_clockDigitShader.GL_ID);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_clockDigitAtlas);

    GLuint coordLoc = m_clockDigitShader.FindUniformLoc("atlasCoordinates");
    TextureUtil::TexCoordinates tc = TextureUtil::GetAtlasCoordinates(8, 4, minutesTens, 1024, 1024);

    glm::vec4 glmTc = glm::vec4(tc.xStart, tc.xEnd, tc.yStart, tc.yEnd);

    glUniform4f(coordLoc, glmTc[0], glmTc[1], glmTc[3], glmTc[2]);

    glBindVertexArray(m_clockVAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    tc = TextureUtil::GetAtlasCoordinates(8, 4, minutesOnes, 1024, 1024);
    glmTc =glm::vec4(tc.xStart, tc.xEnd, tc.yStart, tc.yEnd);
    glUniform4f(coordLoc, glmTc[0], glmTc[1], glmTc[3], glmTc[2]);

    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
    
    tc = TextureUtil::GetAtlasCoordinates(8, 4, secondsTens, 1024, 1024);
    glmTc = glm::vec4(tc.xStart, tc.xEnd, tc.yStart, tc.yEnd);
    glUniform4f(coordLoc, glmTc[0], glmTc[1], glmTc[3], glmTc[2]);

    glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);   
    
    tc = TextureUtil::GetAtlasCoordinates(8, 4, secondsOnes, 1024, 1024);
    glmTc = glm::vec4(tc.xStart, tc.xEnd, tc.yStart, tc.yEnd);
    glUniform4f(coordLoc, glmTc[0], glmTc[1], glmTc[3], glmTc[2]);
        
    glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
    


}

void GameClock::Update(float reading, float dt)
{
    if (!m_Paused) {

        m_TimeElapsed = reading;
        
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
       
        GLuint clockTexCoordBuf = 0;
        glGenBuffers(1, &clockTexCoordBuf);
        
        GLuint ClockVAO = 0;
        glCreateVertexArrays(1, &ClockVAO);
        glBindVertexArray(ClockVAO);

        // Just X and Y coordinates, depth will always be 0
        
        float clockVertices[] = {

            // 10s of minutes
            -1.0f, -1.0f,
            -0.55f, -1.0f,
            -1.0f, 1.0f,
            -0.55f,  1.0f,

            // Minutes
            -0.55f, -1.0f,
            -0.1f, -1.0f,
            -0.55f,  1.0f,
            -0.1f,  1.0f,

            // The ":"
            -0.1f, -1.0f,
             0.1f, -1.0f,
            -0.1f,  1.0f,
             0.1f,  1.0f,

             // 10 seconds
             0.1f, -1.0f,
             0.55f, -1.0f,
             0.1f, 1.0f,
             0.55f, 1.0f,

             // Seconds
             0.55f, -1.0f,
             1.0f, -1.0f,
             0.55f, 1.0f,
             1.0f, 1.0f

        };

        glBindBuffer(GL_ARRAY_BUFFER, clockVB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(clockVertices), clockVertices, GL_STATIC_DRAW);
                       
        float clockTexCoords[]{

            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f

        };

        glBindBuffer(GL_ARRAY_BUFFER, clockTexCoordBuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(clockTexCoords), clockTexCoords, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, clockVB);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, clockTexCoordBuf);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindVertexArray(0);

        return ClockVAO;
}

void GameClock::DrawQuad(Coord2D topLeft, Coord2D bottomRight, Coord2D atlasTopLeft, Coord2D atlasBottomRight)
{
                                        
}
