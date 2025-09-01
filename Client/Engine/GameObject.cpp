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
	// Init transform
	_transform->Init(shared_from_this());
	
	// Init components
	for (auto& component : _components)
		component->Init(shared_from_this());

	// Init renderables
	for (auto& renderable : _renderables)
		renderable->Init(shared_from_this());

	// Init behaviours
	for (auto& behaviour : _bahaviours)
		behaviour->Init(shared_from_this());
}

void GameObject::Update()
{
	// Update children
	for (auto& weakChild : _children)
	{
		if (auto child = weakChild.lock())
			child->Update();
	}

	// Update component
	for (auto& component : _components)
		component->Update();

	// Update renderables
	for (auto& renderable : _renderables)
		renderable->Update();

	// Update Behaviours
	for (auto& behaviour : _bahaviours)
		behaviour->Update();
}
