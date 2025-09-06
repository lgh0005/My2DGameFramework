#pragma once
#include "IRenderable.h"

class ITexture;
class Shader;
class Camera;

class Sprite : public IRenderable
{
	using Super = IRenderable;

public:
	Sprite(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader);
	virtual ~Sprite() override;

public:
	virtual void Init(shared_ptr<GameObject> owner) override;
	virtual void Render(const shared_ptr<Camera>& camera) override;

private:
	shared_ptr<ITexture> _texture;
	shared_ptr<Shader> _shader;
};

