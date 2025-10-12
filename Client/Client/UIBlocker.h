#pragma once
#include "Engine/IBehaviour.h"

class UIBlocker : public IBehaviour
{
	using Super = IBehaviour;

public:
	UIBlocker(const string& name);
	virtual ~UIBlocker() override = default;

public:
	bool IsInteractive();
	void SetInteractive(bool interactive);

private:
	bool _isInteractive;
};

