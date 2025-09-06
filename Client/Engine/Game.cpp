#include "pch.h"
#include "Game.h"
#include "RenderManager.h"

#pragma region TEST
#include "Shader.h"
#include "Texture.h"
#include "Font.h"
#include "Sprite.h"
#include "Transform.h"
#include "Camera.h"
#include "Text.h"
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
    int result = SDL_Init(SDL_INIT_VIDEO);
    LOGGER.DebugAssert(result != 0, "SDL_Init Error", SDL_GetError);

    // Init Font
    result = TTF_Init();
    LOGGER.DebugAssert(result != 0, "SDL_Init Error", nullptr);

    // Init Managers
    RENDER.Init();
    AUDIO.Init();

#pragma region TEST

    // Cameras
    {
        // World Camera
        _worldCamera = make_shared<Camera>("WorldCamera");
        _cameraObjectWorld = make_shared<GameObject>("WorldCameraObject");
        _cameraObjectWorld->AddComponent(_worldCamera);
        _trans2 = make_shared<Transform>
        (
           "t1",
            glm::vec3(300.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );
        _cameraObjectWorld->SetTransform(_trans2);
        RENDER.AddCamera(Render::RenderLayer::World, _worldCamera);
        _cameraObjectWorld->Init();
    }

    // UI Camera
    {
        _uiCamera = make_shared<Camera>("UICamera");
        _cameraObjectUI = make_shared<GameObject>("UICameraObject");
        _cameraObjectUI->AddComponent(_uiCamera);
        _trans3 = make_shared<Transform>
        (
           "t2",
            glm::vec3(300.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );
        _cameraObjectUI->SetTransform(_trans3);
        RENDER.AddCamera(Render::RenderLayer::UI, _uiCamera);
        _cameraObjectUI->Init();
    }

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
    {
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
    }

    // GameObject #1 : GameObject
    {
        // Sprite
        {
            // Texture
            _texture = make_shared<Texture>("texture", "../Resources/Images/cuphead_idle_0001.png");
            RESOURCE.AddResource(_texture);

            // Sprite
            _sprite1 = make_shared<Sprite>("sprite", RESOURCE.GetResource<Texture>("texture"), RESOURCE.GetResource<Shader>("shader1"));
            RENDER.AddRenderable(Render::RenderLayer::World, _sprite1);
        }

        // GameObject and Transform
        _trans1 = make_shared<Transform>
        (
            "transform",
            glm::vec3(300.0f, 200.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        _gameObject = make_shared<GameObject>("GameObject");
        _gameObject->SetTransform(_trans1);
        _gameObject->AddRenderable(static_pointer_cast<IRenderable>(_sprite1));

        _gameObject->Init();
    }

    // GameObject #2 : Text UI
    {
        // Font
        {
            _font = make_shared<Font>("font", "../Resources/Fonts/Crang.ttf", "Hello world!", 64, Colors::White);
            RESOURCE.AddResource(_font);

            // Sprite(UI)
            _sprite2 = make_shared<Text>("Font", RESOURCE.GetResource<Font>("font"), RESOURCE.GetResource<Shader>("shader2"));
            RENDER.AddRenderable(Render::RenderLayer::UI, _sprite2);
        }

        // GameObject and Transform
        _trans4 = make_shared<Transform>
        (
            "transform4",
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        _gameObject2 = make_shared<GameObject>("GameObject2");
        _gameObject2->SetTransform(_trans4);
        _gameObject2->AddRenderable(static_pointer_cast<IRenderable>(_sprite2));

        _gameObject2->Init();
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

            // Input event polling
            INPUT.GetEvent(_event);
        }

        // Update Logic
        Update();

#pragma region TEST
        // Render game
        RENDER.Render();
#pragma endregion
    }
}

void Game::Update()
{
    // Update Managers
    INPUT.Update();

#pragma region TEST
    _gameObject->Update();
    _cameraObjectUI->Update();
    _cameraObjectWorld->Update();

    //if (_sprite1->IsMouseHovered(INPUT.GetMousePosition(_worldCamera)))
    //    cout << "Mouse Hovered!" << endl;

#pragma endregion
}