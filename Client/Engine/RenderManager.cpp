#include "pch.h"
#include "RenderManager.h"
#include "RenderPass.h"

RenderManager::~RenderManager()
{
    if (_glContext) SDL_GL_DeleteContext(_glContext);
    if (_window) SDL_DestroyWindow(_window);
}

void RenderManager::Init()
{
    // Set OpenGL version 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // Create window
    _window = SDL_CreateWindow
    (
        WindowConfig::GameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WindowConfig::GWinSizeX, WindowConfig::GWinSizeY,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    LOGGER.DebugAssert(_window == nullptr, "SDL_CreateWindow Error", SDL_GetError);

    // Get window buffer information
    SDL_GL_GetDrawableSize(_window, &_bufferWidth, &_bufferHeight);

    // Create OpenGL context
    _glContext = SDL_GL_CreateContext(_window);
    LOGGER.DebugAssert(_glContext == nullptr, "SDL_GL_CreateContext Error", SDL_GetError);
    SDL_GL_MakeCurrent(_window, _glContext);

    // Enable modern OpenGL extensions and initialize GLEW
    glewExperimental = GL_TRUE;
    LOGGER.DebugAssert(glewInit() != GLEW_OK, "glewInit Error", glGetError);

    // Create Viewport
    glViewport(0, 0, _bufferWidth, _bufferHeight);
    glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);

    // Enable alpha blending for font/text rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render initialized frame
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(_window);
}

void RenderManager::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& renderPass : _renderQueue)
        renderPass->Render();

    SDL_GL_SwapWindow(_window);
}

void RenderManager::LateUpdate()
{
    for (auto& renderPass : _renderQueue)
    {
        auto& renderables = renderPass->GetRenderables();
        renderables.erase
        (
            remove_if(renderables.begin(), renderables.end(),
            [](const shared_ptr<IRenderable>& renderable) { return renderable->IsPendingDestroy(); }),
            renderables.end()
        );
    }
}

void RenderManager::AddRenderPass(const shared_ptr<RenderPass>& renderPass)
{
    _renderQueue.push_back(renderPass);
}

void RenderManager::SetClearColor(const array<GLclampf, 4>& clearColor)
{
    _clearColor = clearColor;
    glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
}