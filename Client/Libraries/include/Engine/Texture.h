#pragma once
#include "ITexture.h"

class Camera;

class Texture : public ITexture
{
	using Super = ITexture;

public:
	Texture(const string& name, const string& filePath);
	virtual ~Texture() override = default;
};

