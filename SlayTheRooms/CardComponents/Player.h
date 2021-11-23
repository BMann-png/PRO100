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
	Player(int health, pbls::Scene* scene) : health{ health }, scene{ scene }
	{
		Initialize();
	}

	~Player();

	void Initialize();


public:
	int health = 0;
	int attack = 0;
	int defense = 0;
	
	pbls::Scene* scene{ nullptr };
};