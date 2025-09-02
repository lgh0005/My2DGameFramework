#pragma once
#include "ITexture.h"

class Texture : public ITexture
{
	using Super = ITexture;

public:
	Texture(const string& name);
	virtual ~Texture() override;

public:
	virtual void Init() override;
	virtual void Render() override;

public:


private:
};

