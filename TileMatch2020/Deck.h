#pragma once

#include <string>
#include <vector>
// For shader uniform cache
#include <unordered_map>

#include "glad/glad.h"


#include "Card.h"
#include "RenderUtil.h"
#include "SimpleShader.h"

class Deck {

public:

	Deck(int cardX = 2, int cardY = 2, std::string tileSet = "basic");
	~Deck();

	void Update(double dt);
	void Draw(); 

	void Click(double mouseX, double mouseY, int mouseButton);

private:

	GLuint		FindUniform(std::string uniformName);
	CardGeom	CreateCardGeom();

	std::vector<Card> m_Cards;
	std::unordered_map<std::string, GLuint> m_ShaderCache;
	
	CardGeom		m_CardGeom;
	SimpleShader	m_CardShader;

	bool			m_DrawImGui;

};
