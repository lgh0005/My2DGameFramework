#pragma once
#include "IRenderable.h"

class Flipbook;
class Shader;

class FlipbookPlayer : public IRenderable
{
	using Super = IRenderable;

public:
	FlipbookPlayer(const string& name, shared_ptr<Flipbook> flipbook);
	virtual ~FlipbookPlayer() override = default;

public:
	virtual void Awake(const shared_ptr<GameObject>& owner) override;
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) override;
	virtual void Update() override;

public:
	void SetFlipbook(const shared_ptr<Flipbook>& flipbook) { _flipbook = flipbook; }

private:
	shared_ptr<Flipbook> _flipbook;
};

