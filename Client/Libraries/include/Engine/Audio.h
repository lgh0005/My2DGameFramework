#pragma once
#include "IResource.h"

class Audio : public IResource
{
	using Super = IResource;

public:
	Audio(const string& name);
	virtual ~Audio() override;

public:
	virtual void Init() override;

private:

};

