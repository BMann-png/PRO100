#include "Player.h"


Player::~Player()
{

}

void Player::Initialize()
{
	for (int i = 0; i < (int)hand.size(); i++)
	{
		hand[i]->tag = "Player";
		hand[i]->transform.position = {150 + (100 * i), 400};

//		scene->AddActor(std::make_unique<pbls::Actor>(hand[i]));
	}
}
