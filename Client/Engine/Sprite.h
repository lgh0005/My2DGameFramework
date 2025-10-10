#pragma once
#include "IRenderable.h"

class ITexture;

class Sprite : public IRenderable
{
	using Super = IRenderable;

public:
	Sprite(const string& name, shared_ptr<ITexture> texture);
	virtual ~Sprite() override = default;

public:
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) override;

private:
	shared_ptr<ITexture> _texture;
};

