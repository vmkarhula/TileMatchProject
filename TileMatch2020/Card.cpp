#include "Card.h"

#include "CardMath.h"

#include "glad/glad.h"

#include "glm/gtc/matrix_transform.hpp"


Card::Card(Coordinate2D _pos, int _pairID, CamFace _facing) :

	pos2D(_pos),
	pairID(_pairID),
	facing(_facing),
	faceTexSlot(0),
	rotation(0.0f),
	scale(0.5f),
	state(Card::State::FREE),
	releaseTimer(0.0f),
	frontCoordinates(glm::vec4(0.0f)),
	model(glm::mat4(1.0f))
{
	
}

void Card::Turn()
{
	state = Card::State::TURNED;
}

void Card::Freeze()
{
	state = Card::State::FROZEN;
}

void Card::Release(float delay)
{
	
	state = Card::State::DELAYED;
	releaseTimer = delay;

}

void Card::Update(float dt)
{
	
	if (state == Card::State::DELAYED) {

		releaseTimer -= dt; 

		if (releaseTimer <= 0.0) {

			state = Card::State::FREE;
				
		}
	}
	
	if (state == Card::State::TURNED || state == Card::State::DELAYED) {


		if (rotation > 0.0f)
			rotation -= 360.0f * dt;
		
	}

	else {
	
		if (rotation < 180.0f)
			rotation += 360.0f * dt;
	}
	
	rotation = CardMath::clamp(rotation, 0.0f, 180.0f);

	model = glm::translate(glm::mat4(1.0), glm::vec3(pos2D.x, pos2D.y, 0.0f));
	model = glm::scale(model, glm::vec3(scale));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

}

