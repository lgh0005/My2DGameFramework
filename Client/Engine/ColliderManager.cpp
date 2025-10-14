#include "pch.h"
#include "ColliderManager.h"
#include "BoxCollider.h"

void ColliderManager::AddColliderComponent(const shared_ptr<BoxCollider>& collider)
{
	_colliders.push_back(collider);
}

void ColliderManager::RemoveColliderComponent(const shared_ptr<BoxCollider>& collider)
{
	_colliders.erase
	(
		remove(_colliders.begin(), _colliders.end(), collider),
		_colliders.end()
	);
}

void ColliderManager::Clear() { _colliders.clear(); }

void ColliderManager::Update()
{
	for (int i = 0; i < _colliders.size(); i++)
	{
		for (int j = i + 1; j < _colliders.size(); j++)
		{
			auto col1 = _colliders[i];
			auto col2 = _colliders[j];

			if (col1->CheckCollision(col2))
			{
				col1->OnCollisionEnter(col2);
				col2->OnCollisionEnter(col1);
			}
			else
			{
				col1->SetCollisionState(CollisionState::Exit);
				col2->SetCollisionState(CollisionState::Exit);
				col1->OnCollisionExit(col2);
				col2->OnCollisionExit(col1);
				col1->SetCollisionState(CollisionState::None);
				col2->SetCollisionState(CollisionState::None);
			}
		}
	}
}
