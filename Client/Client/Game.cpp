#include "pch.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
    if (_glContext) SDL_GL_DeleteContext(_glContext);
    if (_window) SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

void Game::Init()
{
    // Init SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Set OpenGL version 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // Create window
    _window = SDL_CreateWindow
    (
        "SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    // Get window buffer information
    SDL_GL_GetDrawableSize(_window, &bufferWidth, &bufferHeight);

    // Create OpenGL context
    _glContext = SDL_GL_CreateContext(_window);
    SDL_GL_MakeCurrent(_window, _glContext);

    // 모던 OpenGL Extension들을 허용 및 glew 초기화
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    // 뷰포트 만들기
    glViewport(0, 0, bufferWidth, bufferHeight);
    glClearColor(0.2f, 0.f, 0.f, 1.f);

    // Init Fonts
    TTF_Init();
}

void Game::Launch()
{
    // Event Looping
    while (_running)
    {
        // Event Polling
        while (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
                _running = false;
        }

        Update();
        Render();
    }
}

void Game::Update()
{

}

void Game::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Render Logic here

    SDL_GL_SwapWindow(_window);
}