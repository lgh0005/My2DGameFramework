#pragma once
#include "IComponent.h"

class BoxCollider : public IComponent
{
	using Super = IComponent;

public:
	BoxCollider(const string& name);
	virtual ~BoxCollider() override = default;

public:

private:

};

