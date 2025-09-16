#include "pch.h"
#include "IUIElement.h"
#include "Transform.h"
#include "GameObject.h"
#include "ITexture.h"
#include "Shader.h"

/*=====================
//    Constructor    //
=====================*/
IUIElement::IUIElement(const string& name, const glm::vec2& size) 
	: Super(name), _size(size)
{
}

/*=============================
//    GetWorld Properties    //
=============================*/
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

/*=================================
//    Get Mouse Event boolean    //
=================================*/
bool IUIElement::OnMouseEnter(glm::vec2 mousePos)
{
	auto transform = _owner.lock()->GetTransform();
	glm::vec2 pos = glm::vec2(transform->GetPosition());

	glm::vec2 halfSize = _size * 0.5f;
	glm::vec2 min = pos - halfSize;
	glm::vec2 max = pos + halfSize;

	return (mousePos.x >= min.x && mousePos.x <= max.x &&
		mousePos.y >= min.y && mousePos.y <= max.y);
}

bool IUIElement::OnMouseExit(glm::vec2 mousePos)
{
	return !OnMouseEnter(mousePos);
}

bool IUIElement::OnMouseHovered(glm::vec2 mousePos)
{
	return OnMouseEnter(mousePos);
}

bool IUIElement::OnMouseClick(glm::vec2 mousePos, Inputs::Mouse click)
{
	return OnMouseHovered(mousePos) && INPUT.MouseClick(click);
}

bool IUIElement::OnMouseDragStart(glm::vec2 mousePos, Inputs::Mouse click)
{
	return OnMouseHovered(mousePos) && INPUT.MouseHold(click);
}

bool IUIElement::OnMouseDrag(glm::vec2 mousePos, Inputs::Mouse click)
{
	return OnMouseHovered(mousePos) && INPUT.MouseHold(click);
}

bool IUIElement::OnMouseDragEnd(Inputs::Mouse click)
{
	return INPUT.MouseUp(click);
}

/*======================
//    Event Pusher    //
======================*/
void IUIElement::OnHoveredEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta)
{
	_eventBindings.push_back({ event, GetSelf<IUIElement>(), mousePos, mouseDelta, UI::UIEventType::OnHover, policy });
}

void IUIElement::OnClickedEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta)
{
	_eventBindings.push_back({ event, GetSelf<IUIElement>(), mousePos, mouseDelta, UI::UIEventType::OnClick, policy });
}

void IUIElement::OnExitEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta)
{
	_eventBindings.push_back({ event, GetSelf<IUIElement>(), mousePos, mouseDelta, UI::UIEventType::OnExit, policy });
}

void IUIElement::OnDragStartEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta)
{
	_eventBindings.push_back({ event, GetSelf<IUIElement>(), mousePos, mouseDelta, UI::UIEventType::OnDragStart, policy });
}

void IUIElement::OnDragEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta)
{
	_eventBindings.push_back({ event, GetSelf<IUIElement>(), mousePos, mouseDelta, UI::UIEventType::OnDrag, policy });
}

void IUIElement::OnDragEndEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta)
{
	_eventBindings.push_back({ event, GetSelf<IUIElement>(), mousePos, mouseDelta, UI::UIEventType::OnDragEnd, policy });
}