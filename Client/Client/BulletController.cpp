#include "pch.h"
#include "BulletController.h"

BulletController::BulletController(const string& name) : Super(name)
{
	_bulletShader = RESOURCE.GetResource<Shader>("BulletShader");
	_bulletUniformSet = RESOURCE.GetResource<UniformSet>("BulletUniforms");
}

void BulletController::Init()
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return;

	// TODO : �ݶ��̴��� �޾ƿ;���
}

void BulletController::Update()
{
	MoveBullet();
}

void BulletController::OnCollideWithEnemy(const shared_ptr<BoxCollider>& other)
{
    // TOOD
}

void BulletController::MoveBullet()
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

    glm::vec3 pos = owner->GetTransform()->GetPosition();
    float moveAmount = _speed * TIME.deltaTime;

    if (_direction == Direction::Right)
    {
        pos.x += moveAmount;
        _travelledDistance += moveAmount;

        if (_travelledDistance > _maxMoveDistance)
        {
            owner->Destroy();
            return;
        }
    }
    else if (_direction == Direction::Left)
    {
        pos.x -= moveAmount;
        _travelledDistance -= moveAmount;

        if (_travelledDistance < _minMoveDistance)
        {
            owner->Destroy();
            return;
        }
    }

    // Flip ó��
    if (_bulletUniformSet)
    {
        _bulletUniformSet->Set("flip", _direction == Direction::Left);
        _bulletUniformSet->Apply(_bulletShader);
    }

    owner->GetTransform()->SetPosition(pos);
}


