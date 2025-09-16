#pragma once
#include "IRenderable.h"
#include "UIEvent.h"

struct UIEvent;
class ITexture;
class Shader;

class IUIElement : public IRenderable
{
	using Super = IRenderable;

public:
	IUIElement(const string& name, const glm::vec2& size);
	virtual ~IUIElement() override = default;

protected:
	glm::vec2 GetWorldPosition() const;
	glm::vec2 GetWorldSize() const;

public:
	void OnHoveredEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnClickedEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnExitEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnDragStartEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnDragEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnDragEndEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);

//public:
//	function<void()> GetEnterEvent() const { return _enterEvent; }
//	function<void()> GetHoverEvent() const { return _hoverEvent; }
//	function<void()> GetClickEvent() const { return _clickEvent; }
//	function<void()> GetExitEvent() const { return _exitEvent; }
//	function<void()> GetDragStartEvent() const { return _dragStartEvent; }
//	function<void()> GetDragEvent() const { return _dragEvent; }
//	function<void()> GetDragEndEvent() const { return _dragEndEvent; }

protected:
	bool OnMouseEnter(glm::vec2 mousePos);
	bool OnMouseExit(glm::vec2 mousePos);
	bool OnMouseHovered(glm::vec2 mousePos);
	bool OnMouseClick(glm::vec2 mousePos, Inputs::Mouse click);
	bool OnMouseDragStart(glm::vec2 mousePos, Inputs::Mouse click);
	bool OnMouseDrag(glm::vec2 mousePos, Inputs::Mouse click);
	bool OnMouseDragEnd(Inputs::Mouse click);

protected:
	glm::vec2 _size;
	vector<UIEvent> _eventBindings;

//protected:
//	function<void()> _enterEvent;
//	function<void()> _hoverEvent;
//	function<void()> _clickEvent;
//	function<void()> _exitEvent;
//	function<void()> _dragStartEvent;
//	function<void()> _dragEvent;
//	function<void()> _dragEndEvent;
};