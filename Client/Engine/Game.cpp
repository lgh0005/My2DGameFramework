#include "pch.h"
#include "Game.h"
#include "RenderManager.h"

#pragma region TEST
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#pragma endregion

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

#pragma region TEST

    // Shader
    _shader = make_shared<Shader>("shader", "../Resources/Shaders/VertShader.vert", "../Resources/Shaders/FragShader.frag");

    // Texture
    _texture = make_shared<Texture>("texture", "../Resources/Images/cuphead_idle_0001.png");

    // Sprite
    _sprite = make_shared<Sprite>("sprite", _texture, _shader);
    _sprite->Init(nullptr);
    _shader->AddUniforms({ Uniforms::UNIFORM_MODEL, Uniforms::UNIFORM_VIEW, Uniforms::UNIFORM_PROJECTION, Uniforms::UNIFORM_TEXTURE });
    RENDER.AddRenderable(_sprite);

#pragma endregion
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

#pragma region TEST
        // Render game
        RENDER.Render();
#pragma endregion
    }
}

void Game::Update()
{

}