#pragma once
#include "Engine\IBehaviour.h"

class BGMCheckBoxScript : public IBehaviour
{
	using Super = IBehaviour;

public:
	BGMCheckBoxScript(const string& name);
	virtual ~BGMCheckBoxScript() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void MouseToggle();

private:
	shared_ptr<GameObject> _checkSprite;
	shared_ptr<UICheckBox> _checkBox;
};

