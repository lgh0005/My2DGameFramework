#pragma once
#include "ITexture.h"

class Texture : public ITexture
{
	using Super = ITexture;

public:
	Texture(const string& name, const string& filePath);
	virtual ~Texture() override;

public:
	virtual void Init() override;
	virtual void Render(shared_ptr<Shader> shader, glm::mat4 model) override;
};

