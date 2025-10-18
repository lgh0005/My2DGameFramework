#include "pch.h"
#include "BulletController.h"
#include "EnemyController.h"

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

    // 2. ���� �˻��� �ʿ� ����, ���� ���ο��Լ� ���� ������Ʈ�� �����ɴϴ�.
    _bulletCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("BulletCollider"));

    // 3. ���� "����" �ݶ��̴��� ��Ȯ�� �ݹ��� ����� �� �ֽ��ϴ�.
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

    if (_direction == EDirection::Right) pos.x += moveAmount;
    else if (_direction == EDirection::Left)  pos.x -= moveAmount;

    _travelledDistance += moveAmount;
    if (_travelledDistance > _maxMoveDistance)
    {
        owner->Destroy();
        return;
    }

    if (_bulletUniformSet)
    {
        _bulletUniformSet->Set("flip", _direction == EDirection::Left);
        _bulletUniformSet->Apply(_bulletShader);
    }

    owner->GetTransform()->SetPosition(pos);
}

void BulletController::OnCollisionWithEnemy(const shared_ptr<BoxCollider>& other)
{
    // Get enemy controller
    shared_ptr<GameObject> Other;
    if (Utils::IsValidPtr(other->GetOwner(), Other) == false) return;

    auto enmeyController = static_pointer_cast<EnemyController>(Other->GetBehaviour("EnemyController"));
    if (enmeyController == nullptr) return;

    // 1. ���� ü�� ���
    string otherName = Other->GetName();
    cout << "Collided! with " << otherName << endl;
    // enmeyController->EMOTIONAL_DAMAGE();

    // 2. �Ѿ� �Ҹ�
    shared_ptr<GameObject> owner;
    if (Utils::IsValidPtr(_owner, owner) == false) return;
    owner->Destroy();
    // enmeyController->SetDamage(false);
}


