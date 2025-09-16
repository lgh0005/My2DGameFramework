#pragma once
#include "IUIRenderable.h"

class ITexture;

class UIText : public IUIRenderable
{
	using Super = IUIRenderable;

public:
	UIText(const string& name, shared_ptr<ITexture> font, shared_ptr<Shader> shader, const glm::vec2& size = glm::vec2(1.0f, 1.0f));
	virtual ~UIText() override;
};

