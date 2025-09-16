#include "pch.h"
#include "UIManager.h"
#include "IUIElement.h"
#include "UIEvent.h"

void UIManager::Init()
{

}

void UIManager::Update()
{
	ProcessEvents();
}

void UIManager::CreateEvent(const UI::UIEventType type, const UI::UIEventPolicy policy, 
	weak_ptr<IUIElement> sender, const glm::vec2 mouse, glm::vec2 delta, function<void()> callback)
{
	UIEvent e{ callback, sender, mouse, delta, type, policy };
	PushEvent(e);
}

void UIManager::PushEvent(const UIEvent& e)
{
	switch (e.eventPolicy)
	{
	case UI::UIEventPolicy::Immediate: DispatchEvent(e); break;
	case UI::UIEventPolicy::Deferred: _events.push(e); break;
	}
}

void UIManager::DispatchEvent(const UIEvent& e)
{
	auto uiElement = e.sender.lock();
	if (uiElement != nullptr)
	{
		if (e.callback)
			e.callback();
	}
}

void UIManager::ProcessEvents()
{
	while (!_events.empty())
	{
		UIEvent e = _events.front();
		_events.pop();
		DispatchEvent(e);
	}
}
