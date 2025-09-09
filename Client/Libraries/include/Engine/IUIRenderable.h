#pragma once
#include "IUIElement.h"

class ITexture;
class Shader;
class Camera;

class IUIRenderable : public IUIElement
{
	using Super = IUIElement;

public:
	IUIRenderable(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader);
	virtual ~IUIRenderable() override = default;

public:
	virtual void Awake(shared_ptr<GameObject> owner) override;
	virtual void Render(const shared_ptr<Camera>& camera) override;

protected:
	shared_ptr<ITexture> _texture;
	shared_ptr<Shader> _shader;
};

