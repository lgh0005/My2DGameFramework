#pragma once
#include "IComponent.h"

class IBehaviour : public IComponent
{
	using Super = IComponent;

public:
	IBehaviour(const string& name);
	virtual ~IBehaviour() override = default;

public:
	template<typename T>
	shared_ptr<T> GetSelf()
	{
		return static_pointer_cast<T>(shared_from_this());
	}
};

