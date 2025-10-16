#pragma once
#include "Engine\IBehaviour.h"

class EnemySpawner : public IBehaviour
{
	using Super = IBehaviour;

public:
	EnemySpawner(const string& name);
	virtual ~EnemySpawner() override = default;

public:

};

