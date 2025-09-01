#pragma once
#include "IComponent.h"

class Transform : public IComponent
{
	using Super = IComponent;

public:
	Transform(const string& name);
	virtual ~Transform() override;

public:
	virtual void Init(shared_ptr<GameObject> owner) override;
	virtual void Update() override;

private:
	// TODO : Scale, Rotation, Transform
	// TODO : Dirty Flags
};

