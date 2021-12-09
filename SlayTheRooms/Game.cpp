#include "Game.h"
#include "CardComponents/Player.h"
#include "CardComponents/Card.h"
#include <array>
#include <iostream>


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

	rapidjson::Document document;
	bool success = pbls::json::Load("JsonFiles/scene.txt", document);
	assert(success);

	scene->Read(document);

	engine->Get<pbls::EventSystem>()->Subscribe("cardClick", std::bind(&Game::onClick, this, std::placeholders::_1));

	for (int i = 0; i < 9; i++)
	{
		textures.push_back(engine->Get<pbls::ResourceSystem>()->Get<pbls::Texture>(textureNames[i], engine->Get<pbls::Renderer>()));
	}

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
	case Game::eState::StartShop:
		StartShop();
		break;
	case Game::eState::Shop:
		Shop();
		break;
	case Game::eState::EndShop:
		EndShop();
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

	gold = 5;
	cardBonus = 0;

	std::string title = "Title Screen: Press Space to Start";
	std::cout << title << std::endl;

	scene->RemoveAllActors();
	
	if (playerDied)
	{
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("GameOver")));
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("pressSpace")));
	}
	else
	{
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("TitleBackground")));
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("TitleText")));
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("pressSpace")));
	}

	state = eState::Title;
}

void Game::Title()
{
	if (engine->Get<pbls::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == pbls::InputSystem::eKeyState::Pressed)
	{
		scene->RemoveAllActors();
		state = eState::StartGame;
	}

}

void Game::StartGame()
{
	int nextRoom = pbls::RandomRangeInt(0, 100);
	scene->RemoveAllActors();
	if (nextRoom < 50)
	{
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("FightBackground")));
		turnCount = 0;
		state = eState::StartLevel;
	}
	else if (nextRoom < 75 && nextRoom >= 50)
	{
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("LootBackground")));
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("Chest")));
		state = eState::Loot;
	}
	else
	{
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("ShopBackground")));
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("ShopItem1")));
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("ShopItem2")));
		scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("Goldtxt")));
		state = eState::StartShop;
	}
}

void Game::Combat()
{
	scene->FindActor("PHealthtxt")->GetComponent<pbls::TextComponent>()->SetText("Player Health: " + std::to_string(playerHealth));
	scene->FindActor("PDefensetxt")->GetComponent<pbls::TextComponent>()->SetText("Player Defense: " + std::to_string(playerDefense));
	scene->FindActor("Goldtxt")->GetComponent<pbls::TextComponent>()->SetText(std::to_string(gold) + "gp");
	scene->FindActor("EHealthtxt")->GetComponent<pbls::TextComponent>()->SetText("Enemey Health: " + std::to_string(enemyHealth));
	scene->FindActor("EDefensetxt")->GetComponent<pbls::TextComponent>()->SetText("Enemy Defense: " + std::to_string(enemyDefense));


	if (turnCount == 0)
	{
		player = Player(startingPlayerHealth, scene.get());
		enemy = Player(10, scene.get());
		playerHealth = player.GetHealth();

		player.Initialize();
		
		turnCount += 2;
	}

	if (playerHealth <= 0)
	{
		std::cout << "You Died" << std::endl;

		playerDied = true;

		state = eState::Reset;
	}
	if (enemyHealth <= 0 || turnCount >= 50)
	{
		enemyHealth = 10;
		enemyAttack = enemy.GetAttack();
		enemyDefense = enemy.GetDefense();

		if (turnCount >= 50) std::cout << "By attrition....";
		std::cout << "You Win!!" << std::endl;

		gold += 5;

		std::cout << "Press Space for next room" << std::endl;
		state = eState::Level;
	}
}

void Game::Loot()
{
	if (engine->Get<pbls::InputSystem>()->GetButtonState(0) == pbls::InputSystem::eKeyState::Pressed)
	{
		int addedGold = pbls::RandomRangeInt(0, 10);
		std::cout << "You have gained " << addedGold << " gold!" << std::endl;
		gold += addedGold;
		state = eState::StartGame;
	}
}

void Game::StartShop()
{
	std::cout << "Welcome to the Shop!" << std::endl;

	state = eState::Shop;
}

void Game::Shop()
{
	scene->FindActor("Goldtxt")->GetComponent<pbls::TextComponent>()->SetText(std::to_string(gold) + "gp");
	if (engine->Get<pbls::InputSystem>()->GetButtonState(0) == pbls::InputSystem::eKeyState::Pressed)
	{
		if (gold >= 5)
		{
			if (engine->Get<pbls::InputSystem>()->GetMousePosition().x >= scene->FindActor("ShopItem1")->transform.position.x - 50 && engine->Get<pbls::InputSystem>()->GetMousePosition().x <= scene->FindActor("ShopItem1")->transform.position.x + 50)
			{
				if (engine->Get<pbls::InputSystem>()->GetMousePosition().y >= scene->FindActor("ShopItem1")->transform.position.y - 25 && engine->Get<pbls::InputSystem>()->GetMousePosition().y <= scene->FindActor("ShopItem1")->transform.position.y + 25)
				{
					startingPlayerHealth += 5;
					gold -= 5;
					std::cout << "You Bought HP!" << std::endl;
				}
			}
		}
	}
	if (engine->Get<pbls::InputSystem>()->GetButtonState(0) == pbls::InputSystem::eKeyState::Pressed)
	{
		if(gold >=5)
		{
			if (engine->Get<pbls::InputSystem>()->GetMousePosition().x >= scene->FindActor("ShopItem2")->transform.position.x - 50 && engine->Get<pbls::InputSystem>()->GetMousePosition().x <= scene->FindActor("ShopItem2")->transform.position.x + 50)
			{
				if (engine->Get<pbls::InputSystem>()->GetMousePosition().y >= scene->FindActor("ShopItem2")->transform.position.y - 25 && engine->Get<pbls::InputSystem>()->GetMousePosition().y <= scene->FindActor("ShopItem2")->transform.position.y + 25)
				{
					cardBonus += 1;
					gold -= 5;
					std::cout << "You Bought Damage!" << std::endl;
				}
			}
		}
	}
	if (engine->Get<pbls::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == pbls::InputSystem::eKeyState::Pressed)
	{
		state = eState::EndShop;
	}
		
}

void Game::EndShop()
{
	std::cout << "Thanks for coming!!" << std::endl;
	state = eState::StartGame;
}

void Game::StartLevel()
{
	

	int cardCount = 4;

	for (int i = 0; i < cardCount; i++)
	{
		auto card = pbls::ObjectFactory::Instance().Create<pbls::Actor>("Card");
		card->GetComponent<Card>()->RandomAbility(cardIndex, cardBonus);
		card->GetComponent<pbls::SpriteComponent>()->texture = textures[card->GetComponent<Card>()->GetTexture()];
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

	scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("Player")));
	scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("Enemy")));

	scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("PHealthtxt")));
	scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("PDefensetxt")));
	scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("Goldtxt")));
	scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("EHealthtxt")));
	scene->AddActor(std::move(pbls::ObjectFactory::Instance().Create<pbls::Actor>("EDefensetxt")));

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
		std::cout << cardArray[index]->GetComponent<Card>()->toString() << std::endl;
		playerDefense = player.GetDefense();
		enemyDefense = enemy.GetDefense();
	}
}