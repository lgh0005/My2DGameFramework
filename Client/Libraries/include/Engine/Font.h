#pragma once
#include "ITexture.h"

class Shader;

class Font : public ITexture
{
	using Super = ITexture;

public:
	Font(const string& name, const string& filePath);
	virtual ~Font() override;

public:
	virtual void Init() override;
	virtual void Render(shared_ptr<Shader> shader, glm::mat4 model) override;
	
private:
};

