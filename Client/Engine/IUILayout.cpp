#include "pch.h"
#include "IUILayout.h"

IUILayout::IUILayout(const string& name, const glm::vec2& size)
	: Super(name, size)
{
}

IUILayout::~IUILayout()
{
}
