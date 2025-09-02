#include "pch.h"
#include "Game.h"
#include "RenderManager.h"

unique_ptr<Game> GAME = make_unique<Game>();

Game::Game()
{

}

Game::~Game()
{
    // Release SDL resources
    TTF_Quit();
    SDL_Quit();
}

void Game::Init()
{
    // Init SDL
    LOGGER.DebugAssert(SDL_Init(SDL_INIT_VIDEO) != 0, "SDL_Init Error", SDL_GetError);

    // Init Managers
    RENDER.Init();

    // Init Fonts
    TTF_Init();
}

void Game::Launch()
{
    // Event Looping
    while (_running)
    {
        // Update TimeManager
        TIME.Update();

        // Event Polling
        while (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
                _running = false;
        }

        Update();

        // Render game
        RENDER.Render();
    }
}

void Game::Update()
{

}