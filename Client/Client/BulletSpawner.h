#pragma once
#include "Engine\IBehaviour.h"

class Bullet;

class BulletSpawner : public IBehaviour
{
	using Super = IBehaviour;

public:
	BulletSpawner(const string& name);
	virtual ~BulletSpawner() override = default;

public:
	virtual void Init() override;

public:
	void SpawnBullet(const glm::vec3& position, Direction dir);

private:
	shared_ptr<Bullet> _bulletPrefab;

};

