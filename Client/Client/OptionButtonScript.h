#pragma once
#include "Engine\IBehaviour.h"

class UIBlocker;

class OptionButtonScript : public IBehaviour
{
	using Super = IBehaviour;

public:
	OptionButtonScript(const string& name);
	virtual ~OptionButtonScript() override = default;

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

#pragma region SETTING_UI
private:
	vector<shared_ptr<GameObject>> _settingUIObjects;
	vector<string> _settingUIObjectsName;
#pragma endregion
};

