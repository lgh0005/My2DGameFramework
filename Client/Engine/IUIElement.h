#pragma once
#include "IRenderable.h"

class ITexture;
class Shader;

class IUIElement : public IRenderable
{
	using Super = IRenderable;

public:
	IUIElement(const string& name, const glm::vec2& size);
	virtual ~IUIElement() override;

public:
	virtual void Awake(shared_ptr<GameObject> owner) override;

protected:
	glm::vec2 GetWorldPosition() const;
	glm::vec2 GetWorldSize() const;

protected:
	glm::vec2 _size;
};

