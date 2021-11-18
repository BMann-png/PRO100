#include "Game.h"

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<pbls::Engine>();
	engine->Startup();
	engine->Get<pbls::Renderer>()->Create("GAT150", 800, 600);
	
	//register components
	


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