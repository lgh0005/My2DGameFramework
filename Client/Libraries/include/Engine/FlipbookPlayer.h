#pragma once
#include "IRenderable.h"

class Flipbook;
class Shader;

class FlipbookPlayer : public IRenderable
{
	using Super = IRenderable;

public:
	FlipbookPlayer(const string& name, shared_ptr<Flipbook> flipbook, shared_ptr<Shader> shader);
	virtual ~FlipbookPlayer() override = default;

public:
	virtual void Awake(shared_ptr<GameObject> owner) override;
	virtual void Render(const shared_ptr<Camera>& camera) override;
	virtual void Update() override;

private:
	shared_ptr<Flipbook> _flipbook;
	shared_ptr<Shader> _shader;
};

