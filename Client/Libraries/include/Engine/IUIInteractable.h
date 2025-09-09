#pragma once
#include "IUIElement.h"

class IUIInteractable : public IUIElement
{
	using Super = IUIElement;

public:
	IUIInteractable(const string& name, const glm::vec2& size);
	virtual ~IUIInteractable() override = default;

public:
	void SetHoverEvent(const function<void()>& hoverEvent) { _hoverEvent = hoverEvent; }
	function<void()> GetHoverEvent() const { return _hoverEvent; }
	void SetClickEvent(const function<void()>& clickEvent) { _clickEvent = clickEvent; }
	function<void()> GetClickEvent() const { return _clickEvent; }
	void SetHoldEvent(const function<void()>& holdEvent) { _holdEvent = holdEvent; }
	function<void()> GetHoldEvent() const { return _holdEvent; }

protected:
	bool OnHovered(const glm::vec2& mousePos);
	bool OnClicked(const glm::vec2& mousePos, Inputs::Mouse input);
	bool OnHold(const glm::vec2& mousePos, Inputs::Mouse input);

protected:
	function<void()> _hoverEvent;
	function<void()> _clickEvent;
	function<void()> _holdEvent;
};

