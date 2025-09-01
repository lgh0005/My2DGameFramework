#include "pch.h"
#include "IComponent.h"

IComponent::IComponent(const string& name) : _name(name)
{

}

IComponent::~IComponent()
{

}

void IComponent::Init(shared_ptr<GameObject> owner)
{
	_owner = owner;
}
