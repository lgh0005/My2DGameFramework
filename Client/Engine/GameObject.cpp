#include "pch.h"
#include "GameObject.h"
#include "IComponent.h"
#include "IRenderable.h"
#include "IBehaviour.h"
#include "Transform.h"

GameObject::GameObject(const string& name) : _name(name)
{

}

shared_ptr<IComponent> GameObject::GetComponent(const string& name)
{
	for (auto& component : _components)
	{
		if (component->GetName() == name)
			return component;
	}
	return nullptr;
}

shared_ptr<IRenderable> GameObject::GetRenderable(const string& name)
{
	for (auto& renderable : _renderables)
	{
		if (renderable->GetName() == name)
			return renderable;
	}
	return nullptr;
}

shared_ptr<IBehaviour> GameObject::GetBehaviour(const string& name)
{
	for (auto& behaviour : _behaviours)
	{
		if (behaviour->GetName() == name)
			return behaviour;
	}
	return nullptr;
}

void GameObject::Init()
{
	auto self = shared_from_this();

	// Awake transform, components, renderables, behaviours
	_transform->Awake(self);
	for (auto& component : _components) component->Awake(self);
	for (auto& renderable : _renderables) renderable->Awake(self);
	for (auto& behaviour : _behaviours) behaviour->Awake(self);
	
	// Init transform, components, renderables, behaviours
	_transform->Init();
	for (auto& component : _components) component->Init();
	for (auto& renderable : _renderables) renderable->Init();
	for (auto& behaviour : _behaviours) behaviour->Init();
}

void GameObject::FixedUpdate()
{
	// FixedUpdate component, renderables, Behaviours
	for (auto& component : _components) component->FixedUpdate();
	for (auto& renderable : _renderables) renderable->FixedUpdate();
	for (auto& behaviour : _behaviours) behaviour->FixedUpdate();
}

void GameObject::Update()
{
	if (!_isActive) return;

	// Update component, renderables, Behaviours
	for (auto& component : _components) component->Update();
	for (auto& renderable : _renderables) renderable->Update();
	for (auto& behaviour : _behaviours) behaviour->Update();
}

void GameObject::LateUpdate()
{
	if (!_isActive) return;

	// LateUpdate Transform, component, renderables, Behaviours
	_transform->LateUpdate();
	for (auto& component : _components) component->LateUpdate();
	for (auto& renderable : _renderables) renderable->LateUpdate();
	for (auto& behaviour : _behaviours) behaviour->LateUpdate();
}

void GameObject::SetActive(bool active)
{
	if (_isActive == active) return;
	_isActive = active;

	if (_transform == nullptr) return;
}
