#include "pch.h"
#include "IUIContainer.h"

IUIContainer::IUIContainer(const string& name, const glm::vec2& size)
	: Super(name, size)
{
}

IUIContainer::~IUIContainer()
{
}
