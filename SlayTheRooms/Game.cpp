#include "Game.h"
#include "CardComponents/Player.h"
#include "CardComponents/Card.h"
#include <array>


Player player;

int playerHealth = player.GetHealth();
int playerAttack = player.GetAttack();
int playerDefense = player.GetDefense();

Player enemy;

int enemyHealth = enemy.GetHealth();
int enemyAttack = enemy.GetAttack();
int enemyDefense = enemy.GetDefense();

int turnCount = 0;

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<pbls::Engine>();
	engine->Startup();
	engine->Get<pbls::Renderer>()->Create("GAT150", 800, 600);

	//register components
	REGISTER_CLASS(Card)


	//create scene
	scene = std::make_unique<pbls::Scene>();
	scene->engine = engine.get();

	pbls::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	pbls::SetFilePath("../Resources");

	engine->Get<pbls::EventSystem>()->Subscribe("cardClick", std::bind(&Game::onClick, this, std::placeholders::_1));

}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();

	quit = (engine->Get<pbls::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == pbls::InputSystem::eKeyState::Pressed);

	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	case Game::eState::Combat:
		Combat();
		break;
	case Game::eState::Loot:
		Loot();
		break;
	case Game::eState::Shop:
		Shop();
		break;
	default:
		break;
	}


	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<pbls::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<pbls::Renderer>());
	scene->Draw(engine->Get<pbls::Renderer>());

	engine->Get<pbls::Renderer>()->EndFrame();

}

void Game::Reset()
{
	playerHealth = player.GetHealth();
	playerAttack = player.GetAttack();
	playerDefense = player.GetDefense();

	enemyHealth = enemy.GetHealth();
	enemyAttack = enemy.GetAttack();
	enemyDefense = enemy.GetDefense();

	std::string title = "Title Screen: Press Space to Start";
	std::cout << title << std::endl;
	
	state = eState::Title;
}

void Game::Title()
{
	if (engine->Get<pbls::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == pbls::InputSystem::eKeyState::Pressed)
	{
		state = eState::StartGame;
	}

}

void Game::StartGame()
{
	int nextRoom = pbls::RandomRangeInt(0, 100);
	if (nextRoom < 100)
	{
		turnCount = 0;
		state = eState::StartLevel;
	}/*
	else if (nextRoom < 75 && nextRoom >= 50)
	{
		state = eState::Loot;
	}
	else
	{
		state = eState::Shop;
	}*/
}

void Game::Combat()
{

	if (turnCount == 0)
	{
		player = Player(10, scene.get());
		enemy = Player(10, scene.get());
	}

	if (playerHealth <= 0)
	{
		std::cout << "You Died" << std::endl;

		scene->RemoveAllActors();

		state = eState::Reset;
	}
	if (enemyHealth <= 0)
	{
		enemyHealth = enemy.GetHealth();
		enemyAttack = enemy.GetAttack();
		enemyDefense = enemy.GetDefense();

		std::cout << "You Win!!" << std::endl;

		scene->RemoveAllActors();

		std::cout << "Press Space for next room" << std::endl;
		state = eState::Level;
	}
}

void Game::Loot()
{
	int addedGold = pbls::RandomRangeInt(0, 10);
	std::string loot = "You have gained ";
	loot += addedGold;
	loot += " gold!";
	std::cout << loot << std::endl;
	gold += addedGold;
	state = eState::StartGame;
}

void Game::Shop()
{
	bool shopping = true;

	do
	{
		if (engine->Get<pbls::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == pbls::InputSystem::eKeyState::Pressed)
		{
			gold -= 5;
			shopping = false;
		}
	} while (shopping);

	std::cout << "You bought NOTHING! for 5 gold!" << std::endl;
	state = eState::StartGame;
}

void Game::StartLevel()
{
	rapidjson::Document document;
	bool success = pbls::json::Load("JsonFiles/scene.txt", document);
	assert(success);

	scene->Read(document);

	int cardCount = 4;

	for (int i = 0; i < cardCount; i++)
	{
		auto card = pbls::ObjectFactory::Instance().Create<pbls::Actor>("Card");
		card->GetComponent<Card>()->RandomAbility(cardIndex);
		card->tag = "Player";
		std::cout << card->GetComponent<Card>()->toString() << std::endl;
		scene->AddActor(std::move(card));
		cardIndex++;
	}

	for (int i = 0; i < cardCount; i++)
	{
		auto card = pbls::ObjectFactory::Instance().Create<pbls::Actor>("Card");
		card->GetComponent<Card>()->RandomAbility(cardIndex);
		card->tag = "Enemy";
		cardIndex++;

		cardArray.push_back(std::move(card));

		//scene->AddActor(std::move(card));
	}

	state = eState::Combat;
}

void Game::Level()
{
	if (engine->Get<pbls::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == pbls::InputSystem::eKeyState::Pressed)
	{
		state = eState::StartGame;
	}
}

void Game::PlayerDead()
{

}

void Game::GameOver()
{

}

void Game::onClick(const pbls::Event& event)
{
	pbls::Actor* clickedCard{};

	for (pbls::Actor* card : scene->GetActors<pbls::Actor>())
	{
		if (card->name == "Card")
		{
			if (card->GetComponent<Card>()->index == std::get<int>(event.data))
			{
				clickedCard = card;
			}
		}
	}

	int index = pbls::RandomInt(cardArray.size());

	if (turnCount % 2 == 0)
	{
		std::cout << "Player Turn" << std::endl;
		if (clickedCard->GetComponent<Card>()->GetType() == Card::eType::Damage)
		{
			enemyHealth -= clickedCard->GetComponent<Card>()->GetValue() - (enemyDefense); turnCount++;
			std::cout << "Enemy Health: " << enemyHealth << std::endl;
		}

		if (clickedCard->GetComponent<Card>()->GetType() == Card::eType::Heal)
		{
			playerHealth += clickedCard->GetComponent<Card>()->GetValue(); turnCount++;
			std::cout << "Player Health: " << playerHealth << std::endl;
		}

		if (clickedCard->GetComponent<Card>()->GetType() == Card::eType::Defense)
		{
			playerDefense += clickedCard->GetComponent<Card>()->GetValue(); turnCount++;
			std::cout << "Player Defense: " << playerDefense << std::endl;
		}

		pbls::Event event;
		event.name = "cardClick";
		event.data = index;
		engine->Get<pbls::EventSystem>()->Notify(event);
	}

	else
	{
		std::cout << "Enemy Turn" << std::endl;
		//enemy moves
		if (cardArray[index]->GetComponent<Card>()->GetType() == Card::eType::Damage)
		{
			playerHealth -= cardArray[index]->GetComponent<Card>()->GetValue() - (playerDefense); turnCount++;
			std::cout << "Player Health: " << playerHealth << std::endl;
		}

		if (cardArray[index]->GetComponent<Card>()->GetType() == Card::eType::Heal)
		{
			enemyHealth += cardArray[index]->GetComponent<Card>()->GetValue(); turnCount++;
			std::cout << "Enemy Health: " << enemyHealth << std::endl;
		}

		if (cardArray[index]->GetComponent<Card>()->GetType() == Card::eType::Defense)
		{
			enemyDefense += cardArray[index]->GetComponent<Card>()->GetValue(); turnCount++;
			std::cout << "Enemy Defense: " << enemyDefense << std::endl;
		}
		playerDefense = player.GetDefense();
		enemyDefense = enemy.GetDefense();
	}
}