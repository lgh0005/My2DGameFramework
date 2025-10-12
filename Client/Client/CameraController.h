#pragma once
#include "Engine\IBehaviour.h"

class CameraController : public IBehaviour
{
	using Super = IBehaviour;

public:
	CameraController(const string& name);
	virtual ~CameraController() override = default;

public:
	virtual void Update() override;

private:
	float _moveSpeed = 500.0f;
};
