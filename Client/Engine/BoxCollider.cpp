#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"

BoxCollider::BoxCollider(const string& name, const glm::vec2& size)
	: Super(name), _size(size)
{

}

void BoxCollider::Init()
{
    shared_ptr<GameObject> owner;
    if (Utils::IsValidPtr<GameObject>(_owner, owner))
        _ownerTransform = owner->GetTransform();

    auto self = static_pointer_cast<BoxCollider>(shared_from_this());
    COLLIDER.AddColliderComponent(self);
}

bool BoxCollider::CheckCollision(const shared_ptr<BoxCollider>& other)
{
    if (_ownerTransform == nullptr || other->_ownerTransform == nullptr) return false;

    glm::vec3 posA = _ownerTransform->GetWorldPosition();
    glm::vec3 posB = other->_ownerTransform->GetWorldPosition();

    glm::vec3 worldScaleA = _ownerTransform->GetWorldScale();
    glm::vec3 worldScaleB = other->_ownerTransform->GetWorldScale();

    glm::vec2 finalSizeA = _size * glm::vec2(worldScaleA.x, worldScaleA.y);
    glm::vec2 finalSizeB = other->_size * glm::vec2(worldScaleB.x, worldScaleB.y);

    glm::vec2 halfA = finalSizeA * 0.5f;
    glm::vec2 halfB = finalSizeB * 0.5f;

    bool overlapX = fabs(posA.x - posB.x) < (halfA.x + halfB.x);
    bool overlapY = fabs(posA.y - posB.y) < (halfA.y + halfB.y);

    return overlapX && overlapY;
}

void BoxCollider::OnCollisionEnter(const shared_ptr<BoxCollider>& other)
{
    if (_collisionEnterEvent) _collisionEnterEvent(other);
    _state = CollisionState::Enter;
}

void BoxCollider::OnCollisionExit(const shared_ptr<BoxCollider>& other)
{
    if (_collisionExitEvent) _collisionExitEvent(other);
    _state = CollisionState::Exit;
}
