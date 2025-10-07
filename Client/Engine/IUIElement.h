#pragma once
#include "IRenderable.h"
#include "UIEvent.h"

class Camera;
struct UIEvent;
class ITexture;
class Shader;

class IUIElement : public IRenderable
{
	using Super = IRenderable;

public:
	IUIElement(const string& name, const shared_ptr<Camera>& camera, const glm::vec2& size);
	virtual ~IUIElement() override = default;

protected:
	glm::vec2 GetWorldPosition() const;
	glm::vec2 GetWorldSize() const;

public:
	void OnEnterEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnHoveredEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnClickedEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnExitEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnDragStartEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnDragEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnDragEndEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);
	void OnToggleEvent(function<void()> event, UI::UIEventPolicy policy, glm::vec2 mousePos, glm::vec2 mouseDelta);

public:
	bool IsToggled() { return _toggle; }
	void SetToggle(bool toggle) { _toggle = toggle; }

protected:
	bool OnMouseEnter(glm::vec2 mousePos);
	bool OnMouseExit(glm::vec2 mousePos);
	bool OnMouseHovered(glm::vec2 mousePos);
	bool OnMouseClick(glm::vec2 mousePos, Inputs::Mouse click);
	bool OnMouseDragStart(glm::vec2 mousePos, Inputs::Mouse click);
	bool OnMouseDrag(glm::vec2 mousePos, Inputs::Mouse click);
	bool OnMouseDragEnd(Inputs::Mouse click);
	bool OnToggled(glm::vec2 mousePos, Inputs::Mouse click);

protected:
	bool _toggle = false;
	glm::vec2 _size;
	vector<UIEvent> _eventBindings;
	shared_ptr<Camera> _camera;
};