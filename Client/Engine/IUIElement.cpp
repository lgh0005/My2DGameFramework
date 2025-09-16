#include "pch.h"
#include "IUIElement.h"
#include "Transform.h"
#include "GameObject.h"
#include "ITexture.h"
#include "Shader.h"

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

bool IUIElement::OnHovered(glm::vec2 mousePos)
{
	auto transform = _owner.lock()->GetTransform();
	glm::vec2 pos = glm::vec2(transform->GetPosition());

	glm::vec2 halfSize = _size * 0.5f;
	glm::vec2 min = pos - halfSize;
	glm::vec2 max = pos + halfSize;

	return (mousePos.x >= min.x && mousePos.x <= max.x &&
		mousePos.y >= min.y && mousePos.y <= max.y);
}

bool IUIElement::OnExit(glm::vec2 mousePos)
{
	return !OnHovered(mousePos);
}

bool IUIElement::OnClick(glm::vec2 mousePos, Inputs::Mouse click)
{
	if (OnHovered(mousePos) && INPUT.MouseClick(click)) return true;
	return false;
}

