#pragma once
#include "ISingleton.h"

class IUIInteractable;

struct UIEvent
{
	shared_ptr<IUIInteractable> _uiInteractElement;
	UI::Interaction _type;
};

class UIManager : public ISingleton<UIManager>
{
	DECLARE_SINGLE(UIManager);

public:
	virtual ~UIManager() override = default;

public:

private:
	unordered_map<UI::UIType, vector<IUIInteractable>> _uiElements;
	queue<UIEvent> _eventQueue;
	queue<UIEvent> _nextEventQueue;
};

