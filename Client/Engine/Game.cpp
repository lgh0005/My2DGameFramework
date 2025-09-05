#include "pch.h"
#include "Game.h"
#include "RenderManager.h"

#pragma region TEST
#include "Shader.h"
#include "Texture.h"
#include "Font.h"
#include "Sprite.h"
#include "Transform.h"
#include "GameObject.h"
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

    // Shader : Default texture shader
    {
        _texShader = make_shared<Shader>
        (
            "shader1",
            "../Engine/glsl/default.vert",
            "../Engine/glsl/default.frag",
            vector<const char*>
            {
                Uniforms::UNIFORM_MODEL,
                Uniforms::UNIFORM_VIEW,
                Uniforms::UNIFORM_PROJECTION,
                Uniforms::UNIFORM_TEXTURE
            }
        );
        RESOURCE.AddResource(_texShader);
    }

    // Shader : Defualt text shader
    /*{
        _fontShader = make_shared<Shader>
        (
            "shader2",
            "../Engine/glsl/text.vert",
            "../Engine/glsl/text.frag",
            vector<const char*>
            {
                Uniforms::UNIFORM_MODEL,
                Uniforms::UNIFORM_VIEW,
                Uniforms::UNIFORM_PROJECTION,
                Uniforms::UNIFORM_TEXTURE,
                Uniforms::UNIFORM_COLOR,
            }
        );
        RESOURCE.AddResource(_fontShader);
    }*/

    // Sprite
    {
        // Texture
        _texture = make_shared<Texture>("texture", "../Resources/Images/cuphead_idle_0001.png");
        RESOURCE.AddResource(_texture);

        // Sprite
        _sprite1 = make_shared<Sprite>("sprite", RESOURCE.GetResource<Texture>("texture"), RESOURCE.GetResource<Shader>("shader1"));
        RENDER.AddRenderable(_sprite1);
    }

    //// Font
    //{
    //    _font = make_shared<Font>("font", "../Resources/Fonts/Crang.ttf", "Hello world!", 64, Colors::White);
    //    RESOURCE.AddResource(_font);

    //    // Sprite(UI)
    //    _sprite2 = make_shared<Sprite>("Font", RESOURCE.GetResource<Font>("font"), RESOURCE.GetResource<Shader>("shader2"));
    //    _sprite2->Init(nullptr);
    //    RENDER.AddRenderable(_sprite2);
    //}

    // Transform and GameObject
    {
        _trans1 = make_shared<Transform>
        (
            "transform",
            glm::vec3(300.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        _gameObject = make_shared<GameObject>("GameObject");
        _gameObject->SetTransform(_trans1);
        _gameObject->AddRenderable(static_pointer_cast<IRenderable>(_sprite1));

        _gameObject->Init();
    }

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
    _gameObject->Update();
}