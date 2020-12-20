#pragma once

#include "Coordinate.h"

#include "glm/glm.hpp"

struct Card {

	enum class CamFace { FRONT, BACK };
	enum class State { TURNED, DELAYED, FREE, FROZEN };

	Card(Coordinate2D pos, CamFace facing = CamFace::BACK);
	
	// Turns the card face side up
	void Turn();

	// Locks card in its current state
	void Freeze();

	// Removes the freeze and turns card backside up after the delay   
	void Release(float delay);


	void Update(float dt);

		
	Coordinate2D pos2D;
	CamFace facing;

	int faceTexSlot; 
	
	float rotation;
	float scale;
	
	State state;

	float releaseTimer; 

	glm::vec4 frontCoordinates;
	glm::mat4 model; 
};