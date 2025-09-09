#pragma once
#include "IComponent.h"

class IBehaviour : public IComponent
{
	using Super = IComponent;

public:
	IBehaviour(const string& name);
	virtual ~IBehaviour() override = default;
};

