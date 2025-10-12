#pragma once
#include "IComponent.h"

class Scene;

class IBehaviour : public IComponent
{
	using Super = IComponent;

public:
	IBehaviour(const string& name);
	virtual ~IBehaviour() override = default;

public:
	void SetCurrentScene(const shared_ptr<Scene>& scene);

protected:
	weak_ptr<Scene> _currentScene;
};

