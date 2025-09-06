#pragma once
#include "IUIElement.h"

class ITexture;
class Shader;
class Camera;

class IUIStatic : public IUIElement
{
	using Super = IUIElement;

public:
	IUIStatic(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader);
	virtual ~IUIStatic() override;

public:
	virtual void Init(shared_ptr<GameObject> owner) override;
	virtual void Render(const shared_ptr<Camera>& camera) override;

protected:
	shared_ptr<ITexture> _texture;
	shared_ptr<Shader> _shader;
};

