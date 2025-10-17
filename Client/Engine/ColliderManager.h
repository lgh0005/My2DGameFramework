#pragma once
#include "ISingleton.h"

class BoxCollider;

class ColliderManager : public ISingleton<ColliderManager>
{
	DECLARE_SINGLE(ColliderManager);

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public:
	void AddColliderComponent(const shared_ptr<BoxCollider>& collider);

public:
	void Clear();

private:
	vector<shared_ptr<BoxCollider>> _colliders;
};

