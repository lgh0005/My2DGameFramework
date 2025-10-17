#include "pch.h"
#include "ColliderManager.h"
#include "BoxCollider.h"
#include "GameObject.h"

void ColliderManager::AddColliderComponent(const shared_ptr<BoxCollider>& collider)
{
	_colliders.push_back(collider);
}

void ColliderManager::Clear() { _colliders.clear(); }

void ColliderManager::Init() {}

void ColliderManager::Update()
{
	// detect collision
	for (int i = 0; i < _colliders.size(); i++)
	{
		for (int j = i + 1; j < _colliders.size(); j++)
		{
			auto col1 = _colliders[i];
			auto col2 = _colliders[j];

			// Check if collders are detectable
			if (col1->IsPendingDestroy() || col2->IsPendingDestroy()) continue;
			if (col1->IsActive() == false || col2->IsActive() == false) continue;

			shared_ptr<GameObject> col1Owner;
			shared_ptr<GameObject> col2Owner;
			if (!Utils::IsValidPtr(col1->GetOwner(), col1Owner) || !Utils::IsValidPtr(col2->GetOwner(), col2Owner)) continue;
			if (!col1Owner->IsActive() || !col2Owner->IsActive()) continue;
			
			bool canCollide = (col1->GetMask() & col2->GetLayer()) != CollisionLayer::Layers::None &&
				(col2->GetMask() & col1->GetLayer()) != CollisionLayer::Layers::None;

			if (!canCollide) continue;

			// detect collision
			if (col1->CheckCollision(col2))
			{
				col1->OnCollisionEnter(col2);
				col2->OnCollisionEnter(col1);
			}
			else
			{
				col1->OnCollisionExit(col2);
				col2->OnCollisionExit(col1);
			}
		}
	}
}

void ColliderManager::LateUpdate()
{
	_colliders.erase
	(
		remove_if(_colliders.begin(), _colliders.end(),
		[](const shared_ptr<BoxCollider>& collider) { return collider->IsPendingDestroy(); }),
		_colliders.end()
	);
}