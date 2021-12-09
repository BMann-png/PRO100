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
		if (card->GetComponent<Card>() && card->tag == "Player")
		{
			card->transform.position = { 175 + (150 * i), 300 };
			i++;

			std::string name = "card" + std::to_string(i) + "Name";
			std::string value = "card" + std::to_string(i) + "Value";

			card->AddChild(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>(name)));
			card->AddChild(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>(value)));

			card->children[0]->GetComponent<pbls::TextComponent>()->SetText(card->GetComponent<Card>()->GetName());
			card->children[0]->transform.localPosition.y = -1000;
			card->children[0]->transform.localScale = { 10, 10 };

			card->children[1]->GetComponent<pbls::TextComponent>()->SetText(card->GetComponent<Card>()->GetTypeString() + std::to_string(card->GetComponent<Card>()->GetValue()));
			card->children[1]->transform.localPosition.y = 1000;
			card->children[1]->transform.localScale = { 10, 10 };
		}
	}


	scene->engine->Get<pbls::EventSystem>()->Subscribe("onClick", std::bind(&Player::onClick, this, std::placeholders::_1));
}

void Player::onClick(const pbls::Event& event)
{

}