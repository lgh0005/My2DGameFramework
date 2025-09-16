#pragma once
#include "ISingleton.h"

class IUIInteractable;

class UIManager : public ISingleton<UIManager>
{
	DECLARE_SINGLE(UIManager);

public:
	virtual ~UIManager() override = default;

public:


private:


};

