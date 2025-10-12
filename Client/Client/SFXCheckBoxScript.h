#pragma once
#include "Engine\IBehaviour.h"

class SFXCheckBoxScript : public IBehaviour
{
	using Super = IBehaviour;

public:
	SFXCheckBoxScript(const string& name);
	virtual ~SFXCheckBoxScript() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void MouseToggle();

private:
	shared_ptr<GameObject> _checkSprite;
	shared_ptr<UICheckBox> _checkBox;
};

