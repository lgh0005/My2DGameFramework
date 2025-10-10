#pragma once
#include "Engine\IBehaviour.h"

class OptionButtonScript : public IBehaviour
{
	using Super = IBehaviour;

public:
	OptionButtonScript(const string& name);
	virtual ~OptionButtonScript() override = default;

public:
	virtual void Init() override;

private:
	shared_ptr<UIButton> _button;
	void MouseHovered();
	void MouseExit();
	void MouseClickedDeferred();
	void MouseClickedImmediate();
};

