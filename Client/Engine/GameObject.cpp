#include "pch.h"
#include "GameObject.h"
#include "IComponent.h"
#include "IRenderable.h"
#include "IBehaviour.h"
#include "BoxCollider.h"
#include "Transform.h"

GameObject::GameObject(const string& name) : _name(name)
{

}

GameObject::~GameObject()
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

void GameObject::SetParent(const shared_ptr<GameObject>& parent)
{
	_parent = parent;
	if (parent) parent->AddChild(shared_from_this());
}

void GameObject::Destroy()
{
	SetActive(false);
	_pendingDestroy = true;

	for (auto& component : _components) component->Destroy();
	for (auto& renderable : _renderables) renderable->Destroy();
	for (auto& behaviour : _behaviours) behaviour->Destroy();

	for (auto& child : _children)
	{
		if (child)
			child->Destroy();
	}

	/* FOR DEFENCE */
	{
		_transform = nullptr;
		_parent.reset(); // weak_ptr¸¦ ºñ¿ó´Ï´Ù.

		_components.clear();
		_renderables.clear();
		_behaviours.clear();
		_children.clear();
	}
}

void GameObject::SetActive(bool active)
{
	if (_isActive == active) return;
	_isActive = active;

	if (_transform) _transform->SetActive(active);
	for (auto& component : _components) component->SetActive(active);
	for (auto& renderable : _components) renderable->SetActive(active);
	for (auto& behaviour : _components) behaviour->SetActive(active);

	for (auto& child : _children)
	{
		if (child)
			child->SetActive(active);
	}

	if (_transform == nullptr) return;
}

