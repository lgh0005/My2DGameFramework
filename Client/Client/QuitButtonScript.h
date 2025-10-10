#pragma once
#include "Engine/IBehaviour.h"

class QuitButtonScript : public IBehaviour
{
	using Super = IBehaviour;

public:
	QuitButtonScript(const string& name);
	virtual ~QuitButtonScript() override = default;

public:
	virtual void Init() override;

private:
	bool _sfxPlayFlag = true;

private:
	shared_ptr<UIButton> _button;
	void MouseHovered();
	void MouseExit();
	void MouseClickedDeferred();
	void MouseClickedImmediate();
};

