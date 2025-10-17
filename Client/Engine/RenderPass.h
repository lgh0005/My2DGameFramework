#pragma once
#include "UniformSet.h"

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
	shared_ptr<Shader> GetShader() { return _shader; }
	void SetCamera(const shared_ptr<Camera>& camera) { _camera = camera; }
	shared_ptr<Camera> GetCamera() { return _camera; }
	void AddRenderable(const shared_ptr<IRenderable>& renderable) { _renderables.push_back(renderable); }
	vector<shared_ptr<IRenderable>>& GetRenderables() { return _renderables; }
	void SetUniformSet(const shared_ptr<UniformSet>& uniformSet) { _customUniforms = uniformSet; }

public:
	template<typename T>
	void SetUniform(const string& name, const T& value)
	{
		_customUniforms->Set(name, value);
	}

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Camera> _camera;
	vector<shared_ptr<IRenderable>> _renderables;
	shared_ptr<UniformSet> _customUniforms;
};

