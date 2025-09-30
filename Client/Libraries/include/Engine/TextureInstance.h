#pragma once
#include "ITextureInstance.h"

class TextureInstance : public ITextureInstance
{
	using Super = ITextureInstance;

public:
	TextureInstance(const string& name, const string& filePath);
	virtual ~TextureInstance() override = default;
};

