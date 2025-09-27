#pragma once
#include "IUIRenderable.h"

class ITexture;
class Camera;

class UIText : public IUIRenderable
{
	using Super = IUIRenderable;

public:
	UIText(const string& name, shared_ptr<Camera> camera, shared_ptr<ITexture> font, const glm::vec2& size = glm::vec2(1.0f, 1.0f));
	virtual ~UIText() override = default;

public:
	virtual void Awake(const shared_ptr<GameObject>& owner) override;
};

