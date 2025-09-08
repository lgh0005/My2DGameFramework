#pragma once
#include "IComponent.h"

class IBehaviour : public IComponent
{
	using Super = IComponent;

public:
	IBehaviour(const string& name);
	virtual ~IBehaviour() override;

public:
	virtual void Awake(shared_ptr<GameObject> owner);
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void LateUpdate();
};

