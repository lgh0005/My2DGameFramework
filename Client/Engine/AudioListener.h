#pragma once
#include "IComponent.h"

class AudioListener : public IComponent
{
	using Super = IComponent;

public:
	AudioListener(const string& name);
	virtual ~AudioListener() override;

public:
	virtual void Update() override;

private:

};

