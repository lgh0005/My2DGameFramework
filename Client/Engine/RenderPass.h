#pragma once

class Shader;
class Camera;
class IRenderable;

class RenderPass
{
public:
	RenderPass() = default;
	~RenderPass() = default;

public:
	void Render();

public:
	void SetShader(const shared_ptr<Shader>& shader) { _shader = shader; }
	void SetCamera(const shared_ptr<Camera>& camera) { _camera = camera; }
	shared_ptr<Camera> GetCamera() { return _camera; }
	void AddRenderable(const shared_ptr<IRenderable>& renderable) { _renderables.push_back(renderable); }

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Camera> _camera;
	vector<shared_ptr<IRenderable>> _renderables;
};

