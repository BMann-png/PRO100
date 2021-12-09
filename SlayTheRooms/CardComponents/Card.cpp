#include "Card.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>
#include "Framework/EventSystem.h"

Card::Card(std::string name, int index, int value, int type)
{
	this->index = index;
	ability.name = name;
	ability.value = value;
	ability.type = static_cast<eType>(type);

}

std::string Card::GetTypeString()
{
	switch ((int)ability.type)
	{
	case 0:
		return "damage";
			break;
	case 1:
		return "defense";
			break;
	case 2:
		return "heal";
			break;
	default:
		break;
	}
	return std::string();
}

void Card::RandomAbility(int index, int CardBonus)
{
	int i = pbls::RandomInt(8);
	ability.name = abilities[i];
	switch (i)
	{
	case 0:
		ability.type = (eType)0;
		break;
	case 1:
		ability.type = (eType)0;
		break;
	case 2:
		ability.type = (eType)0;
		break;
	case 3:
		ability.type = (eType)1;
		break;
	case 4:
		ability.type = (eType)1;
		break;
	case 5:
		ability.type = (eType)1;
		break;
	case 6:
		ability.type = (eType)2;
		break;
	case 7:
		ability.type = (eType)2;
		break;
	case 8:
		ability.type = (eType)2;
		break;

	default:
		break;
	}
	ability.value = pbls::RandomInt(5) + 1;

	texture = i;

	if (i < 3)
	{
		ability.value += CardBonus;
	}

	this->index = index;

}

void Card::Create()
{
}

void Card::Update()
{
	if (owner->scene->engine->Get<pbls::InputSystem>()->GetButtonState(0) == pbls::InputSystem::eKeyState::Pressed)
	{
		pbls::Vector2 mousePos = owner->scene->engine->Get<pbls::InputSystem>()->GetMousePosition();
		if (mousePos.x > owner->transform.position.x - 75 && mousePos.x < owner->transform.position.x + 75)
		{
			if (mousePos.y > owner->transform.position.y - 75 && mousePos.y < owner->transform.position.y + 75)
			{
				//player moves
				if (ability.type == Card::eType::Damage) {}
				if (ability.type == Card::eType::Heal) {}
				if (ability.type == Card::eType::Defense) {}

				//enemy moves
				if (ability.type == Card::eType::Damage) {}
				if (ability.type == Card::eType::Heal) {}
				if (ability.type == Card::eType::Defense) {}

				//owner->destroy = true;
				std::cout << toString() << std::endl;

				pbls::Event event;
				event.name = "cardClick";
				event.data = index;

				owner->scene->engine->Get<pbls::EventSystem>()->Notify(event);

			}
		}
	}
}

bool Card::Write(const rapidjson::Value& value) const
{
	return false;
}

bool Card::Read(const rapidjson::Value& value)
{
	return false;
}

std::string Card::toString()
{
	std::string toReturn;
	std::string type;

	switch (static_cast<int>(ability.type))
	{
	case 0:
		type = "Damage";
		break;
	case 1:
		type = "Defense";
		break;
	case 2:
		type = "Heal";
		break;
	default:
		break;
	}

	toReturn = "Spell: " + ability.name + ", Type: " + type + ", Value: " + std::to_string(ability.value);

	return toReturn;
}