#pragma once
#include "Engine.h"
#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>
#include <cassert>

class Game
{
public:
	enum class eState
	{
		Reset,
		Title,
		StartGame,
		StartLevel,
		Level,
		PlayerDead,
		GameOver,
		Combat,
		Loot,
		Shop
	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:
	void Reset();
	void Title();
	void StartGame();
	void Combat();
	void Loot();
	void Shop();
	void StartLevel();
	void Level();
	void PlayerDead();
	void GameOver();
	void onClick(const pbls::Event& event);


public:
	std::unique_ptr<pbls::Engine> engine;
	std::unique_ptr<pbls::Scene> scene;

private:
	bool quit{ false };

	eState state = eState::Reset;
	int score{ 0 };
	float stateTimer{ 0 };
	float spawnTimer{ 0 };
	int cardIndex = 0;

	int gold = 0;

	std::vector<std::unique_ptr<pbls::Actor>> cardArray;
};