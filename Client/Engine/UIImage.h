#pragma once
#include "IUIRenderable.h"

class ITexture;
class Camera;

class UIImage : public IUIRenderable
{
	using Super = IUIRenderable;

public:
	UIImage(const string& name, shared_ptr<Camera> camera,
		shared_ptr<ITexture> image, shared_ptr<Shader> shader, const glm::vec2& size = glm::vec2(1.0f, 1.0f));
	virtual ~UIImage() override;
};

