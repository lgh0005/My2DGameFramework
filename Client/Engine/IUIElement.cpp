#include "pch.h"
#include "IUIElement.h"
#include "Transform.h"
#include "GameObject.h"
#include "ITexture.h"
#include "Shader.h"
#include "IUIInteractable.h"

IUIElement::IUIElement(const string& name, const glm::vec2& size) 
	: Super(name), _size(size)
{
}

glm::vec2 IUIElement::GetWorldPosition() const
{
	auto owner = _owner.lock();
	if (!owner) return glm::vec2(1.0f);

	auto transform = owner->GetTransform();
	return glm::vec2(transform->GetPosition());
}

glm::vec2 IUIElement::GetWorldSize() const
{
	auto owner = _owner.lock();
	if (!owner) return glm::vec2(1.0f);

	auto transform = owner->GetTransform();
	glm::vec2 scale = glm::vec2(transform->GetScale());
	return _size * scale;
}