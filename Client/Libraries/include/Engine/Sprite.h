#pragma once
#include "IRenderable.h"

class Texture;
class Shader;

class Sprite : public IRenderable
{
	using Super = IRenderable;

public:
	Sprite(const string& name, shared_ptr<Texture> texture, shared_ptr<Shader> shader);
	virtual ~Sprite() override;

public:
	virtual void Init(shared_ptr<GameObject> owner) override;
	virtual void Render() override;

private:
	shared_ptr<Texture> _texture;
	shared_ptr<Shader> _shader;
};

