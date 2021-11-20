#include "Game.h"

#include "CardComponents/Player.h"
#include "CardComponents/Card.h"

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<pbls::Engine>();
	engine->Startup();
	engine->Get<pbls::Renderer>()->Create("GAT150", 800, 600);
	
	//register components
	REGISTER_CLASS(pbls::Card)


	//create scene
	scene = std::make_unique<pbls::Scene>();
	scene->engine = engine.get();

	pbls::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	pbls::SetFilePath("../Resources");


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
	default:
		break;
	}

	
	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	

}

void Game::Reset()
{
	rapidjson::Document document;
	bool success = pbls::json::Load("JsonFiles/scene.txt", document);
	assert(success);

	scene->Read(document);


	std::vector<pbls::Actor*> newHand;

	for (int i = 0; i < 4; i++)
	{
		newHand.push_back(pbls::ObjectFactory::Instance().Create<pbls::Actor>("Card").get());
		newHand[i]->GetComponent<pbls::Card>()->RandomAbility();
	}

	Player player(100, newHand, scene.get());

}

void Game::Title()
{
	
}

void Game::StartGame()
{
	
}

void Game::StartLevel()
{
	
}

void Game::Level()
{
	
}

void Game::PlayerDead()
{
	
}

void Game::GameOver()
{

}