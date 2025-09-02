#pragma once
#include "IComponent.h"

class Camera : public IComponent
{
	using Super = IComponent;

public:
	Camera(const string& name);
	virtual ~Camera() override;

public:
	virtual void Update() override;

private:

};

