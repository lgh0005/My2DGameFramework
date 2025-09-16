#pragma once
#include "IUIElement.h"

class ITexture;
class Shader;
class Camera;

class IUIRenderable : public IUIElement
{
	using Super = IUIElement;

public:
	IUIRenderable(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader, const glm::vec2& size);
	virtual ~IUIRenderable() override;

public:
	virtual void Awake(shared_ptr<GameObject> owner) override;
	virtual void Render(const shared_ptr<Camera>& camera) override;

public:
	shared_ptr<ITexture> GetTexture() { return _texture; }
	void SetTexture(shared_ptr<ITexture> texture) { _texture = texture; }
	shared_ptr<Shader> GetShader() { return _shader; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }

protected:
	shared_ptr<ITexture> _texture;
	shared_ptr<Shader> _shader;
};

