#pragma once

#include <string>
#include <vector>
// For shader uniform cache
#include <unordered_map>
#include <random>

// For cerr
#include <iostream>

#include "glad/glad.h"

#include "Card.h"
#include "RenderUtil.h"
#include "SimpleShader.h"
#include "DeckUtils.h"



class Deck {

public:

	enum class GameSize{ TINY, SMALL, MEDIUM, LARGE };
	enum class GameState{ IN_PROGRESS, SOLVED, READY_TO_PLAY };

	Deck(GameSize gameSize = GameSize::TINY, std::string tileSet = "basic");
	~Deck();

	Deck::GameState Update(double dt);
	//void DrawPerspective();
	void DrawOrthographic();

	void Click(double mouseX, double mouseY, int mouseButton);

	void Shuffle(int seed = 0); 

private:

	//GLuint		FindUniform(std::string uniformName);
	CardGeom	CreateCardGeom();
	void		ResolveSelection();

	PaddingData m_Padding = { 0.05, 0.05, 0.05, 0.05 };

	int m_NumCardsX;
	int m_NumCardsY;

	int m_MaxSelected = 2;



	std::vector<Card> m_Cards;

	std::vector<Card*>		m_Selected;
		
	CardGeom				m_CardGeom;

	GLuint					m_CardBackTexID;
	GLuint					m_CardFrontAtlasID;
	
	SimpleShader			m_CardSideShader;
	SimpleShader			m_CardBackShader;
	SimpleShader			m_CardFrontShader;

	bool					m_DrawImGui;
	
	std::mt19937			m_RNG;
	
	int						m_Score;
};
