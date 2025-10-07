#pragma once
#include "Engine\IBehaviour.h"

class UIButton;
class Shader;

class example2 : public IBehaviour
{
	using Super = IBehaviour;

public:
	example2(const string& name);
	virtual ~example2() override;

public:
	virtual void Init() override;
	virtual void Update() override;

private:
	shared_ptr<UIButton> _button;
	void MouseHovered();
	void MouseExit();
	void MouseClickedDeferred();
	void MouseClickedImmediate();

private:
	bool _playOnce = true;
};

