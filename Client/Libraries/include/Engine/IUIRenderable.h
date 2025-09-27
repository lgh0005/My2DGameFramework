#pragma once
#include "IUIElement.h"

class ITexture;
class Shader;
class Camera;

class IUIRenderable : public IUIElement
{
	using Super = IUIElement;

public:
	IUIRenderable(const string& name, const shared_ptr<Camera>& camera, shared_ptr<ITexture> texture, const glm::vec2& size);
	virtual ~IUIRenderable() override = default;

public:
	virtual void Awake(const shared_ptr<GameObject>& owner) override;
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) override;

public:
	shared_ptr<ITexture> GetTexture() { return _texture; }
	void SetTexture(shared_ptr<ITexture> texture) { _texture = texture; }

protected:
	shared_ptr<ITexture> _texture;
};

