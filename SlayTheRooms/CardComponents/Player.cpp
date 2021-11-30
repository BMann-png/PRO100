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


	scene->engine->Get<pbls::EventSystem>()->Subscribe("onClick", std::bind(&Player::onClick, this, std::placeholders::_1));
}

void Player::onClick(const pbls::Event& event)
{

}