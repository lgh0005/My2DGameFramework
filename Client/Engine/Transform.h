#pragma once
#include "IComponent.h"

class Transform : public IComponent
{
	using Super = IComponent;

public:
	Transform(const string& name);
	virtual ~Transform() override;

private:
	// TODO : Scale, Rotation, Transform
	// TODO : Dirty Flags
};

