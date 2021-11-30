#pragma once
#include <vector>
#include <memory>

#include "Card.h"
#include "Object/Scene.h"
#include "Object/Actor.h"
#include "Engine.h"

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

	int GetHealth() { return health; }
	int GetAttack() { return attack; }
	int GetDefense() { return defense; }

	void onClick(const pbls::Event& event);

public:
	int health = 10;
	int attack = 0;
	int defense = 0;

	pbls::Scene* scene{ nullptr };
};