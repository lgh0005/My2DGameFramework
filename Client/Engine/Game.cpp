#include "pch.h"
#include "Game.h"
#include "Scene.h"

unique_ptr<Game> GAME = make_unique<Game>();

Game::~Game()
{    
    // Release SDL resources
    TTF_Quit();
    SDL_Quit();
}

void Game::Init()
{
    // Init SDL
    int result = SDL_Init(SDL_INIT_VIDEO);
    LOGGER.DebugAssert(result != 0, "SDL_Init Error", SDL_GetError);

    // Init Font
    result = TTF_Init();
    LOGGER.DebugAssert(result != 0, "SDL_Init Error", nullptr);

    // Init Managers
    RENDER.Init();
    AUDIO.Init();
}

void Game::Launch(const string& FirstSceneName)
{
    // Load first scene
    SCENE.LoadScene(FirstSceneName);

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

            // Input event polling
            INPUT.GetEvent(_event);
        }

        // Update Logic
        Update();
    }
}

void Game::Update()
{
    // Update Managers
    SCENE.Update();
    COLLIDER.Update();
    INPUT.Update();
    AUDIO.Update();
    UIMANAGER.Update();
    RENDER.Update();
}

void Game::Quit()
{
    _running = false;
}
