#include "pch.h"
#include "IComponent.h"

IComponent::IComponent(const string& name) : _name(name)
{

}

void IComponent::Awake(const shared_ptr<GameObject>& owner) { _owner = owner; }
void IComponent::Init() {}
void IComponent::Update() {}
void IComponent::FixedUpdate() {}
void IComponent::LateUpdate() {}
