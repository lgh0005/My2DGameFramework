#pragma once
#include "IResource.h"

class Flipbook : public IResource
{
	using Super = IResource;

public:
	Flipbook(const string& name);
	virtual ~Flipbook() override;

public:
	virtual void Init() override;

private:

};

