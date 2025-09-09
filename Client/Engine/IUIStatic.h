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
	virtual ~IUIStatic() override = default;

public:
	virtual void Awake(shared_ptr<GameObject> owner) override;
	virtual void Render(const shared_ptr<Camera>& camera) override;

protected:
	// TODO : �׷��� Canvas�� ���� Texture�� �ʿ���� ���� ��� ����?
	shared_ptr<ITexture> _texture;
	shared_ptr<Shader> _shader;
};

