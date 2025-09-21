#pragma once
#include "Engine\IBehaviour.h"

class UICheckBox;

class example3 : public IBehaviour
{
	using Super = IBehaviour;

public:
	example3(const string& name);
	virtual ~example3() override;

public:
	virtual void Init() override;
	virtual void Update() override;

private:
	shared_ptr<UICheckBox> _checkBox;
	void MouseToggle();


};

