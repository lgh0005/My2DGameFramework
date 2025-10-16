#include "pch.h"
#include "BulletController.h"
#include "BulletCollideScript.h"

BulletController::BulletController(const string& name) : Super(name)
{
	_bulletShader = RESOURCE.GetResource<Shader>("BulletShader");
	_bulletUniformSet = RESOURCE.GetResource<UniformSet>("BulletUniforms");
}

void BulletController::Init()
{
    auto self = GetSelf<BulletController>();

    shared_ptr<GameObject> owner;
    if (Utils::IsValidPtr(_owner, owner) == false) return; 

    // Get bullet and bullet collider
    _bulletCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("BulletCollider"));
    _bulletCollider->ClearCollisionEnterCallback();
    _bulletCollider->SetCollisionEnterCallback([self](const shared_ptr<BoxCollider>& other) { self->OnCollisionWithEnemy(other); });
}

void BulletController::Update()
{
	MoveBullet();
}

void BulletController::MoveBullet()
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

    glm::vec3 pos = owner->GetTransform()->GetPosition();
    float moveAmount = _speed * TIME.deltaTime;

    if (_direction == Direction::Right) pos.x += moveAmount;
    else if (_direction == Direction::Left)  pos.x -= moveAmount;

    _travelledDistance += moveAmount;
    if (_travelledDistance > _maxMoveDistance)
    {
        owner->Destroy();
        return;
    }

    if (_bulletUniformSet)
    {
        _bulletUniformSet->Set("flip", _direction == Direction::Left);
        _bulletUniformSet->Apply(_bulletShader);
    }

    owner->GetTransform()->SetPosition(pos);
}

void BulletController::OnCollisionWithEnemy(const shared_ptr<BoxCollider>& other)
{
    // TODO
    // 1. 적의 생명을 2깎는다.
    // 2. 이 오브젝트 소멸. 주의할 것은 이 오브젝트(BulletCollider) 뿐만 아니라,
    // 이 오브젝트 부모도 없애야함.

    // DEBUG
    shared_ptr<GameObject> Other;
    if (Utils::IsValidPtr(other->GetOwner(), Other) == false) return;

    string otherName = Other->GetName();
    cout << "Collided! with " << otherName << endl;
}


