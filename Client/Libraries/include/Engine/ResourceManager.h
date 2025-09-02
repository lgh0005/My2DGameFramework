#pragma once
#include "ISingleton.h"

class ResourceManager : public ISingleton<ResourceManager>
{
	DECLARE_SINGLE(ResourceManager);

public:
	virtual void Init() override;
	virtual void Update() override;

private:

};

