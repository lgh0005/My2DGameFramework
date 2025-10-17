#include "pch.h"
#include "IComponent.h"
#include "GameObject.h"

IComponent::IComponent(const string& name) : _name(name)
{

}

void IComponent::Awake(const shared_ptr<GameObject>& owner) { _owner = owner; }
void IComponent::Init() { if (!IsActive()) return; }
void IComponent::Update() { if (!IsActive()) return; }
void IComponent::FixedUpdate() { if (!IsActive()) return; }
void IComponent::LateUpdate() { if (!IsActive()) return; }