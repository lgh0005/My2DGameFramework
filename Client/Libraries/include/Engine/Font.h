#pragma once
#include "ITexture.h"

class Shader;
class Camera;

class Font : public ITexture
{
	using Super = ITexture;

public:
	Font(const string& name, const string& filePath, const string& text, uint32 fontSize, SDL_Color color);
	virtual ~Font() override;

public:
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) override;
	
protected:
	virtual void LoadTexture() override;
	
private:
	string _text;
	uint32 _fontSize;
	SDL_Color _color;
};

