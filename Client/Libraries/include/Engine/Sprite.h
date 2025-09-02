#pragma once
#include "IRenderable.h"

class Sprite : public IRenderable
{
	using Super = IRenderable;

public:
	Sprite(const string& name);
	virtual ~Sprite() override;

public:
	virtual void Update() override;

private:

};

