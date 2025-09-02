#pragma once
#include "ITexture.h"

class Font : public ITexture
{
	using Super = ITexture;

public:
	Font(const string& name);
	virtual ~Font() override;

public:
	virtual void Init() override;
	virtual void Render() override;
	
private:
};

