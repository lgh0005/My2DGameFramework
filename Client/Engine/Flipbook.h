#pragma once
#include "ITexture.h"

class Flipbook : public ITexture
{
	using Super = ITexture;

public:
	Flipbook(const string& name);
	virtual ~Flipbook() override;

public:
	virtual void Init() override;
	virtual void Render() override;

private:

};

