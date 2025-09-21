#pragma once
#include "Engine\IBehaviour.h"

class example1 : public IBehaviour
{
	using Super = IBehaviour;

public:
	example1(const string& name);
	virtual ~example1() override = default;

public:
	virtual void Update() override;
};

