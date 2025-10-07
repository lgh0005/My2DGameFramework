#pragma once
#include "ISingleton.h"

class Camera;
class RenderPass;

class RenderManager : public ISingleton<RenderManager>
{
	DECLARE_SINGLE(RenderManager);

public:
	virtual ~RenderManager() override;

public:
	virtual void Init() override;
	virtual void Update() override;

#pragma region ADD_RENDER_PASS_TEST
public:
	//void AddRenderable(Render::RenderLayer layer, shared_ptr<IRenderable> renderable);
	void AddRenderPass(const shared_ptr<RenderPass>& renderPass);
	void Clear() { _renderQueue.clear(); }

#pragma endregion
	
public:
	void SetClearColor(const array<GLclampf, 4>& clearColor);

private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
	int _bufferWidth = 0;
	int _bufferHeight = 0;
	array<GLclampf, 4> _clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };

private:
	vector<shared_ptr<RenderPass>> _renderQueue;
};