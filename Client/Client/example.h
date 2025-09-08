#pragma once
#include "Engine/IBehaviour.h"

class example : public IBehaviour
{
	using Super = IBehaviour;

public:
	example(const string& name);
	virtual ~example() override;

public:
	virtual void Update() override;
};

