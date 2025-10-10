#pragma once
#include "ISingleton.h"

class BoxCollider;

class ColliderManager : public ISingleton<ColliderManager>
{
	DECLARE_SINGLE(ColliderManager);

public:
	virtual void Init() override {};
	virtual void Update() override;

public:
	void AddColliderComponent(const shared_ptr<BoxCollider>& collider);
	void RemoveColliderComponent(const shared_ptr<BoxCollider>& collider);

private:
	vector<shared_ptr<BoxCollider>> _colliders;
};

