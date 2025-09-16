#pragma once
#include "ISingleton.h"
#include "UIEvent.h"

class IUIElement;
struct UIEvent;

class UIManager : public ISingleton<UIManager>
{
	DECLARE_SINGLE(UIManager);

public:
	virtual ~UIManager() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void CreateEvent(const UI::UIEventType type, const UI::UIEventPolicy policy,
		weak_ptr<IUIElement> sender, const glm::vec2 mouse, glm::vec2 delta, function<void()> callback);

private:
	void PushEvent(const UIEvent& e);
	void DispatchEvent(const UIEvent& e);
	void ProcessEvents();

private:
	queue<UIEvent> _events;
};

