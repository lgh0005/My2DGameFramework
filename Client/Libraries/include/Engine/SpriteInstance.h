#pragma once
#include "IRenderable.h"

class ITextureInstance;

class SpriteInstance : public IRenderable
{
	using Super = IRenderable;

public:
	SpriteInstance(const string& name, shared_ptr<ITextureInstance> texture);
	virtual ~SpriteInstance() override = default;

public:
	virtual void Awake(const shared_ptr<GameObject>& owner) override;
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) override;

public:
	void AddModelMatrix(const glm::mat4& model);

private:
	shared_ptr<ITextureInstance> _texture;
};

