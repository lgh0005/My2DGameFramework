#pragma once
#include "Engine\IBehaviour.h"

class UIButton;
class UIBlocker;

class StartButtonScript : public IBehaviour
{
	using Super = IBehaviour;

public:
	StartButtonScript(const string& name);
	virtual ~StartButtonScript() override = default;

public:
	virtual void Init() override;

private:
	shared_ptr<UIBlocker> _uiBlockerComponent;

private:
	bool _sfxPlayFlag = true;

private:
	shared_ptr<UIButton> _button;
	void MouseHovered();
	void MouseExit();
	void MouseClickedDeferred();
	void MouseClickedImmediate();
};

