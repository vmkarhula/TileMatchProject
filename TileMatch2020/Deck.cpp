#include "Deck.h"

#include "glm/gtc/type_ptr.hpp"

#include <assert.h>

Deck::Deck(GameSize gameSize, std::string tileSet) :

    m_NumCardsX(0),
    m_NumCardsY(0),
    m_CardGeom(CreateCardGeom()),
    m_CardBackTexID(LoadUtil::LoadTexture(".\\resource\\testi.png")),
    m_CardFrontAtlasID(LoadUtil::LoadTexture(".\\resource\\atlas_dice.png")),
    m_CardSideShader(".\\shader\\cardflip.vs.glsl", ".\\shader\\basic.fs.glsl"),
    m_CardBackShader(".\\shader\\cardback.vs.glsl", ".\\shader\\cardback.fs.glsl"),
    m_CardFrontShader(".\\shader\\cardfront.vs.glsl", ".\\shader\\cardfront.fs.glsl")


{
    // Make sure uniforms are cached
    m_CardSideShader.FindUniformLoc("modelMtx");
    m_CardSideShader.FindUniformLoc("projMtx");
    m_CardSideShader.FindUniformLoc("viewMtx");

    m_CardBackShader.FindUniformLoc("modelMtx");
    m_CardBackShader.FindUniformLoc("projMtx");
    m_CardBackShader.FindUniformLoc("viewMtx");
    m_CardBackShader.FindUniformLoc("texture1");

    m_CardFrontShader.FindUniformLoc("modelMtx");
    m_CardFrontShader.FindUniformLoc("projMtx");
    m_CardFrontShader.FindUniformLoc("viewMtx");
    m_CardFrontShader.FindUniformLoc("texture1");
    m_CardFrontShader.FindUniformLoc("atlasCoordinates");

    
    switch (gameSize)
    {
    case GameSize::TINY: {

        m_NumCardsX = 6;
        m_NumCardsY = 2; 

    } break;

    case GameSize::SMALL:
    case GameSize::MEDIUM:
    case GameSize::LARGE:
    {
        std::cerr << "ERROR, UNIMPLEMENTED GAME SIZE" << std::endl;

    } break;
   
    
    default:
        break;
    }

    
    double deltaY = 2.0 / m_NumCardsY;
    double deltaX = 2.0 / m_NumCardsX;

    for (int i = 0; i < m_NumCardsY; i++) {

        for (int j = 0; j < m_NumCardsX; j++) {
            
            Card newCard(Coordinate2D{ static_cast<float>(0.5 * deltaX + j * deltaX -1.0f), static_cast < float>(0.5f * deltaY + i * deltaY - 1.0f )}, Card::CamFace::BACK);
            newCard.scale = 0.5*std::min(deltaX, deltaY);
            
            TextureHelp::TexCoordinates coords = TextureHelp::GetAtlasCoordinates(4, 4, 0, 512, 512);

            newCard.frontCoordinates = glm::vec4(coords.xStart, coords.xEnd, coords.yStart, coords.yEnd);
            m_Cards.push_back(newCard);
        }

    }
}

Deck::~Deck()
{
}

void Deck::Update(double dt)
{
	for (Card& c : m_Cards)
		c.Update(dt);

}

/*void Deck::DrawPerspective()
{
	
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw the rim
	

    // Draw the cards
    m_CardSideShader.Bind();
	
    GLuint modelLoc = FindUniform("model");
    GLuint viewLoc = FindUniform("view");
    GLuint projLoc = FindUniform("proj");

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    float aspect = 800.0f / 600.0f;
    glm::mat4 proj = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);
   
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	

	for (const Card& c : m_Cards){
		
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(c.model));
		glDrawElements(GL_TRIANGLES, m_CardGeom.FrontVCount, GL_UNSIGNED_INT, nullptr);
	}


}*/

void Deck::DrawOrthographic()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the rim


    // Draw the cards
    m_CardFrontShader.Bind();

    GLuint modelLoc = m_CardFrontShader.FindUniformLoc("modelMtx");
    GLuint viewLoc = m_CardFrontShader.FindUniformLoc("viewMtx");
    GLuint projLoc = m_CardFrontShader.FindUniformLoc("projMtx");

    GLuint atlasCoordLoc = m_CardFrontShader.FindUniformLoc("atlasCoordinates");
    GLuint tex1Loc = m_CardFrontShader.FindUniformLoc("texture1");

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 30.0f);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_CardFrontAtlasID);
    glUniform1i(tex1Loc, 0);

    // Frontsides
    glBindVertexArray(m_CardGeom.FrontVAO);
       
    for (const Card& c : m_Cards) {

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(c.model));
        glUniform4f(atlasCoordLoc, c.frontCoordinates[0], c.frontCoordinates[1], c.frontCoordinates[2], c.frontCoordinates[3]);
        glDrawElements(GL_TRIANGLES, m_CardGeom.FrontVCount, GL_UNSIGNED_INT, nullptr);
    }


    // Backsides
    glUseProgram(m_CardBackShader.GL_ID);
    glBindVertexArray(m_CardGeom.BackVAO);

    modelLoc = m_CardBackShader.FindUniformLoc("modelMtx");
    viewLoc = m_CardBackShader.FindUniformLoc("viewMtx");
    projLoc = m_CardBackShader.FindUniformLoc("projMtx");

    tex1Loc = m_CardBackShader.FindUniformLoc("texture1");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_CardBackTexID);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    glUniform1i(tex1Loc, 0);

    for (const Card& c : m_Cards) {

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(c.model));
        glDrawElements(GL_TRIANGLES, m_CardGeom.BackVCount, GL_UNSIGNED_INT, nullptr);
    }

    // Sides
    glUseProgram(m_CardSideShader.GL_ID);
    glBindVertexArray(m_CardGeom.SideVAO);

    modelLoc = m_CardSideShader.FindUniformLoc("modelMtx");
    viewLoc = m_CardSideShader.FindUniformLoc("viewMtx");
    projLoc = m_CardSideShader.FindUniformLoc("projMtx");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    for (const Card& c : m_Cards) {

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(c.model));
        glDrawElements(GL_TRIANGLES, m_CardGeom.SideVCount, GL_UNSIGNED_INT, nullptr);

    }

    glBindVertexArray(0);

}

void Deck::Click(double mouseX, double mouseY, int mouseButton)
{
    int target = 0;

    int x, y;

    y = m_NumCardsY * mouseY; 
    x = m_NumCardsX * mouseX;

    target = m_NumCardsX * y + x;
    
   if (m_Cards[target].state == Card::State::FREE) {

        m_Cards[target].Turn();
        m_Selected.push_back(&m_Cards[target]);
    
        if (m_Selected.size() >= m_MaxSelected) {

            ResolveSelection();
        }

    }
}

/*GLuint Deck::FindUniform(std::string uniformName)
{
	auto search = m_ShaderCache.find(uniformName);

	// If we can't find the uniform, query opengl for location and cache it
	if (search == m_ShaderCache.end()) {

		GLuint uniformID = glGetUniformLocation(m_CardSideShader.GL_ID, uniformName.c_str());
		m_ShaderCache[uniformName] = uniformID;
		return uniformID;
	}

	// If we got it cached
	else 
		return search->second;

}
*/
CardGeom Deck::CreateCardGeom()
{
    /*Card Front Area*/
    
    GLuint CardFrontVB = 0;
    glGenBuffers(1, &CardFrontVB);

    GLuint CardFrontIB = 0;
    glGenBuffers(1, &CardFrontIB);

    GLuint FrontTexCoordBuf = 0;
    glGenBuffers(1, &FrontTexCoordBuf);

    float frontVertices[] = {

     
        -0.5f,  0.8f,  -0.1f,
        -0.5f, -0.8f,  -0.1f,
         0.5f, -0.8f,  -0.1f,
         0.5f,  0.8f,  -0.1f,

    };

    float frontTexCoords[] = {
       
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
        
    };

    unsigned int frontIndices[] = {

       
         2, 1, 0,
         2, 0, 3

         
    };

    GLuint FrontVAO;
    glCreateVertexArrays(1, &FrontVAO);

    glBindVertexArray(FrontVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CardFrontVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(frontVertices), frontVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CardFrontIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(frontIndices), frontIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, FrontTexCoordBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(frontTexCoords), frontTexCoords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, CardFrontVB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, FrontTexCoordBuf);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    CardGeom geom;

    geom.FrontVAO = FrontVAO;
    geom.FrontVCount = sizeof(frontIndices);


    /* Card Back Area */

    GLuint CardBackVB = 0;
    glGenBuffers(1, &CardBackVB);

    GLuint CardBackIB = 0;
    glGenBuffers(1, &CardBackIB);

    GLuint BackTexCoordBuf = 0;
    glGenBuffers(1, &BackTexCoordBuf);

    float backVertices[] = {

        -0.5f,  0.8f,  0.1f,
        -0.5f, -0.8f,  0.1f,
         0.5f, -0.8f,  0.1f,
         0.5f,  0.8f,  0.1f, 

    };

    float backTexCoords[] = {
        
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
    };

    unsigned int backIndices[] = {

         0, 1, 2,
         3, 0, 2,
    };

    GLuint BackVAO;
    glCreateVertexArrays(1, &BackVAO);

    glBindVertexArray(BackVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CardBackVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(backVertices), backVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CardBackIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backIndices), backIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, BackTexCoordBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(backTexCoords), backTexCoords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, CardBackVB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BackTexCoordBuf);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    geom.BackVAO = BackVAO;
    geom.BackVCount = sizeof(backIndices);

    // Sides
    GLuint SideVB = 0;
    glGenBuffers(1, &SideVB);

    GLuint SideIB = 0;
    glGenBuffers(1, &SideIB);

    GLuint SideColorBuf = 0;
    glGenBuffers(1, &SideColorBuf);

    float sideVertices[]{
        
        -0.5f,  0.8f, -0.1f,
        -0.5f, -0.8f, -0.1f,
        -0.5f, -0.8f,  0.1f,
        -0.5f,  0.8f,  0.1f,

        0.5f,  0.8f, -0.1f,
        0.5f, -0.8f, -0.1f,
        0.5f, -0.8f,  0.1f,
        0.5f,  0.8f,  0.1f,

       -0.5f, 0.8f, -0.1f,
       -0.5f, 0.8f,  0.1f,
        0.5f, 0.8f,  0.1f,
        0.5f, 0.8f, -0.1f,

       -0.5f, -0.8f, -0.1f,
       -0.5f, -0.8f,  0.1f,
        0.5f, -0.8f,  0.1f,
        0.5f, -0.8f, -0.1f
    };

    float sideColors[]{

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f

    };

    unsigned int sideIndices[]{
    
        // Left
         0, 1, 2,
         3, 0, 2,

         // Right
         6, 5, 4,
         6, 4, 7,

         // Top
         8, 9, 10,
         11, 8, 10,

         // Bottom
         14, 13, 12,
         14, 12, 15

    };

    GLuint SideVAO;
    glCreateVertexArrays(1, &SideVAO);

    glBindVertexArray(SideVAO);

    glBindBuffer(GL_ARRAY_BUFFER, SideVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sideVertices), sideVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SideIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sideIndices), sideIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, SideColorBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sideColors), sideColors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, SideVB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, SideColorBuf);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    geom.SideVAO = SideVAO;
    geom.SideVCount = sizeof(sideIndices);

	return geom;
}

void Deck::ResolveSelection()
{
    for (Card* card : m_Selected) {

        card->Release(1.0f);
        
    }

    m_Selected.clear();
}



