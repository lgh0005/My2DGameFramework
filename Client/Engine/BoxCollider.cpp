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
}

bool BoxCollider::CheckCollision(const shared_ptr<BoxCollider>& other)
{
    glm::vec3 posA = _ownerTransform->GetPosition();
    glm::vec3 posB = other->_ownerTransform->GetPosition();

    glm::vec2 halfA = _size * 0.5f;
    glm::vec2 halfB = other->_size * 0.5f;

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
