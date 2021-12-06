#include "Player.h"

Player::~Player()
{

}

void Player::Initialize()
{
	std::vector<pbls::Actor*> hand = scene->GetActors<pbls::Actor>();

	int i = 0;

	for (pbls::Actor* card : hand)
	{
		if (card->GetComponent<Card>())
		{
			card->transform.position = { 175 + (150 * i), 300 };
			i++;
		}
	}


	scene->engine->Get<pbls::EventSystem>()->Subscribe("onClick", std::bind(&Player::onClick, this, std::placeholders::_1));
}

void Player::onClick(const pbls::Event& event)
{

}