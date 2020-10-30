#include "Card.h"

#include "CardMath.h"

#include "glad/glad.h"

#include "glm/gtc/matrix_transform.hpp"


Card::Card(Coordinate2D _pos, CamFace _facing) :

	pos2D(_pos),
	facing(_facing),
	rotation(0.0f),
	model(glm::mat4(1.0f)),
	scale(0.5f)
{
	
}

void Card::Update(float dt)
{
	/*if (facing == Card::CamFace::BACK && rotation < 180.0f)
		rotation += 180.0f * dt;

	else if (facing == Card::CamFace::FRONT && rotation > 0.0f)
		rotation -= 180.0f * dt;
	*/
	
	//rotation = CardMath::clamp(rotation, 0.0f, 180.0f);

	model = glm::translate(glm::mat4(1.0), glm::vec3(pos2D.x, pos2D.y, 0.0f));
	model = glm::scale(model, glm::vec3(scale));
	model = glm::rotate(model, glm::half_pi<float>() + glm::half_pi<float>() * glm::sin(dt), glm::vec3(0.0f, 1.0f, 0.0f));

	// Based on the updates, readjust the model matrix
	//model = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::translate(glm::mat4(1.0f), glm::vec3(pos2D.x, pos2D.y, 0.0f));

}
