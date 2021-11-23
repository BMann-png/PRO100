#include "Player.h"


Player::~Player()
{

}

void Player::Initialize()
{
	std::vector<pbls::Actor*> hand = scene->GetActors<pbls::Actor>();

	for (int i = 0; i < hand.size(); i++)
	{
		hand[i]->transform.position = { 175 + (150 * i), 300 };
	}
}
