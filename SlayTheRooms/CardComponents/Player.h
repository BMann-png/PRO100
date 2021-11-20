#pragma once
#include <vector>
#include <memory>

#include "Card.h"
#include "Object/Scene.h"
#include "Object/Actor.h"

class Player
{
		
public:
	Player() = default;
	Player(int health, std::vector<pbls::Actor*> newHand, pbls::Scene* scene) : health{ health }, scene{ scene }
	{
		for (int i = 0; i < (int)newHand.size(); i++)
		{
			hand.push_back(newHand[i]);
		}

		Initialize();
	}

	~Player();

	void Initialize();


public:
	int health = 0;
	int attack = 0;
	int defense = 0;
	std::vector<pbls::Actor*> hand;

	pbls::Scene* scene{ nullptr };
};