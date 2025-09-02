#pragma once
#include "IComponent.h"

class AudioSource : public IComponent
{
	using Super = IComponent;

public:
	AudioSource(const string& name);
	virtual ~AudioSource() override;

public:
	virtual void Update() override;

private:

};

