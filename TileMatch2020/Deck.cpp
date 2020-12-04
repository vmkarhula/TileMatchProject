#include "Deck.h"

#include "glm/gtc/type_ptr.hpp"

#include <assert.h>

Deck::Deck(GameSize gameSize, std::string tileSet) :

    m_NumCardsX(0),
    m_NumCardsY(0),
    m_CardGeom(CreateCardGeom()),
    m_CardShader(".\\shader\\cardflip.vs.glsl", ".\\shader\\basic.fs.glsl")

{
    
	m_ShaderCache["model"] = glGetUniformLocation(m_CardShader.GL_ID, "modelMtx");
	m_ShaderCache["proj"] = glGetUniformLocation(m_CardShader.GL_ID, "projMtx");
	m_ShaderCache["view"] = glGetUniformLocation(m_CardShader.GL_ID, "viewMtx");
    
    switch (gameSize)
    {
    case GameSize::TINY: {

        m_NumCardsX = 5;
        m_NumCardsY = 5; 

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

void Deck::DrawPerspective()
{
	
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw the rim
	

    // Draw the cards
    m_CardShader.Bind();
	
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
		glDrawElements(GL_TRIANGLES, m_CardGeom.CardVertexCount, GL_UNSIGNED_INT, nullptr);
	}


}

void Deck::DrawOrthographic()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the rim


    // Draw the cards
    m_CardShader.Bind();

    GLuint modelLoc = FindUniform("model");
    GLuint viewLoc = FindUniform("view");
    GLuint projLoc = FindUniform("proj");

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 30.0f);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


    for (const Card& c : m_Cards) {

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(c.model));
        glDrawElements(GL_TRIANGLES, m_CardGeom.CardVertexCount, GL_UNSIGNED_INT, nullptr);
    }
}

void Deck::Click(double mouseX, double mouseY, int mouseButton)
{
    int target = 0;

    int x, y;

    y = m_NumCardsY * mouseY; 
    x = m_NumCardsX * mouseX;

    target = m_NumCardsX * y + x;
    
    if (m_Cards[target].facing == Card::CamFace::BACK){
        
        m_Cards[target].facing = Card::CamFace::FRONT;
        m_Selected.push_back(&m_Cards[target]);
    }

    else if (m_Cards[target].facing == Card::CamFace::FRONT){
       
        m_Cards[target].facing = Card::CamFace::BACK;
        m_Selected.push_back(&m_Cards[target]);
    }

    if (m_Selected.size() >= m_MaxSelected) {

        ResolveSelection();
    }

}

GLuint Deck::FindUniform(std::string uniformName)
{
	auto search = m_ShaderCache.find(uniformName);

	// If we can't find the uniform, query opengl for location and cache it
	if (search == m_ShaderCache.end()) {

		GLuint uniformID = glGetUniformLocation(m_CardShader.GL_ID, uniformName.c_str());
		m_ShaderCache[uniformName] = uniformID;
		return uniformID;
	}

	// If we got it cached
	else 
		return search->second;

}

CardGeom Deck::CreateCardGeom()
{
    GLuint cardVB = 0;
    glGenBuffers(1, &cardVB);

    GLuint cardIB = 0;
    glGenBuffers(1, &cardIB);

    GLuint cardColorBuf = 0;
    glGenBuffers(1, &cardColorBuf);

    float cardVertices[] = {

        -0.5f,  0.8f,  0.1f,
        -0.5f, -0.8f,  0.1f,
         0.5f, -0.8f,  0.1f,
         0.5f,  0.8f,  0.1f,

        -0.5f,  0.8f,  -0.1f,
        -0.5f, -0.8f,  -0.1f,
         0.5f, -0.8f,  -0.1f,
         0.5f,  0.8f,  -0.1f,

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

    float cardColors[] = {

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

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

    unsigned int cardIndices[] = {

        // Front face
         0, 1, 2,
         3, 0, 2,

         // Back
         6, 5, 4,
         6, 4, 7,

         // Left
         8, 9, 10,
         11, 8, 10,

         // Right
         14, 13, 12,
         14, 12, 15,

         // Top
         16, 17, 18,
         19, 16, 18,

         // Bottom
         22, 21, 20,
         22, 20, 23,

    };

    GLuint CardVAO;
    glCreateVertexArrays(1, &CardVAO);

    glBindVertexArray(CardVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cardVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cardVertices), cardVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cardIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cardIndices), cardIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, cardColorBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cardColors), cardColors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, cardVB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, cardColorBuf);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    CardGeom geom;

    geom.CardVAO = CardVAO;
    geom.CardVertexCount = sizeof(cardIndices);

	return geom;
}

void Deck::ResolveSelection()
{
    for (Card* card : m_Selected) {

        card->facing = Card::CamFace::BACK;
    }

    m_Selected.clear();
}



