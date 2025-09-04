#pragma once
#include "ISingleton.h"

class IRenderable;

class RenderManager : public ISingleton<RenderManager>
{
	DECLARE_SINGLE(RenderManager);

public:
	virtual ~RenderManager() override;

public:
	virtual void Init() override;
	virtual void Update() override;
	void Render();

#pragma region TEST
	void AddRenderable(shared_ptr<IRenderable> renderable);
#pragma endregion

private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
	int _bufferWidth = 0;
	int _bufferHeight = 0;
	array<GLclampf, 4> _clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };

#pragma region TEST
	vector<shared_ptr<IRenderable>> _renderables;
#pragma endregion
};