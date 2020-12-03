#pragma once

#include <string>
#include <vector>
// For shader uniform cache
#include <unordered_map>

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

	Deck(GameSize gameSize = GameSize::TINY, std::string tileSet = "basic");
	~Deck();

	void Update(double dt);
	void DrawPerspective();
	void DrawOrthographic();

	void Click(double mouseX, double mouseY, int mouseButton);

private:

	GLuint		FindUniform(std::string uniformName);
	CardGeom	CreateCardGeom();
	void		ResolveSelection();

	PaddingData m_Padding = { 0.05, 0.05, 0.05, 0.05 };

	int m_NumCardsX;
	int m_NumCardsY;

	int m_MaxSelected = 2;



	std::vector<Card> m_Cards;
	std::unordered_map<std::string, GLuint> m_ShaderCache;
	
	std::vector<Card*>		m_Selected;
		
	CardGeom				m_CardGeom;
	SimpleShader			m_CardShader;

	bool					m_DrawImGui;
	
	
};
