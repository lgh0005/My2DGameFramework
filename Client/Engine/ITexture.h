#pragma once
#include "IResource.h"

class ITexture : public IResource
{
public:
	ITexture(const string& name);
	virtual ~ITexture();

public:
	virtual void Render();

protected:
	// OpenGL stuff.
};

