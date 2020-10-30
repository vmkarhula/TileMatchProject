#pragma once

#include "Coordinate.h"

#include "glm/glm.hpp"

struct Card {

	enum class CamFace {FRONT, BACK};
	
	Card(Coordinate2D pos, CamFace facing = CamFace::BACK);
	void Update(float dt);


	Coordinate2D pos2D;
	CamFace facing;
	float rotation;
	float scale;

	glm::mat4 model; 
};