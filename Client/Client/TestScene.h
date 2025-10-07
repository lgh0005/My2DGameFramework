#pragma once
#include "Engine\Scene.h"

class TestScene : public Scene
{
	using Super = Scene;

public:
	TestScene(const string& name);
	virtual ~TestScene() override = default;

protected:
	virtual void CreateSceneContext() override;
};

