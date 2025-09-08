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
	for (auto& behaviour : _bahaviours)
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
	for (auto& behaviour : _bahaviours) behaviour->Awake(self);
	
	// Init transform, components, renderables, behaviours
	_transform->Init();
	for (auto& component : _components) component->Init();
	for (auto& renderable : _renderables) renderable->Init();
	for (auto& behaviour : _bahaviours) behaviour->Init();
}

void GameObject::FixedUpdate()
{
	// FixedUpdate children
	for (auto& weakChild : _children)
	{
		if (auto child = weakChild.lock()) child->FixedUpdate();
	}

	// FixedUpdate component, renderables, Behaviours
	for (auto& component : _components) component->FixedUpdate();
	for (auto& renderable : _renderables) renderable->FixedUpdate();
	for (auto& behaviour : _bahaviours) behaviour->FixedUpdate();
}

void GameObject::Update()
{
	// Update children
	for (auto& weakChild : _children)
	{
		if (auto child = weakChild.lock()) child->Update();
	}

	// Update component, renderables, Behaviours
	for (auto& component : _components) component->Update();
	for (auto& renderable : _renderables) renderable->Update();
	for (auto& behaviour : _bahaviours) behaviour->Update();
}

void GameObject::LateUpdate()
{
	// LateUpdate children
	for (auto& weakChild : _children)
	{
		if (auto child = weakChild.lock()) child->LateUpdate();
	}

	// LateUpdate component, renderables, Behaviours
	for (auto& component : _components) component->LateUpdate();
	for (auto& renderable : _renderables) renderable->LateUpdate();
	for (auto& behaviour : _bahaviours) behaviour->LateUpdate();
}