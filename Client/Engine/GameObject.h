#pragma once

class IComponent;
class IRenderable;
class IBehaviour;
class Transform;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject(const string& name);
	~GameObject();

public:
	void AddComponent(const shared_ptr<IComponent>& component) { _components.push_back(component); }
	void AddRenderable(const shared_ptr<IRenderable>& renderable) { _renderables.push_back(renderable); }
	void AddBehaviour(const shared_ptr<IBehaviour>& behaviour) { _behaviours.push_back(behaviour); }

	// Component Getters
public:
	shared_ptr<IComponent> GetComponent(const string& name);
	shared_ptr<IRenderable> GetRenderable(const string& name);
	shared_ptr<IBehaviour> GetBehaviour(const string& name);

	// Init and Update
public:
	void Init();
	void FixedUpdate();
	void Update();
	void LateUpdate();

	// Properties
public:
	// Getter : name
	const string& GetName() { return _name; }

	// Getter and Setter : transform
	shared_ptr<Transform> GetTransform() { return _transform; }
	void SetTransform(const shared_ptr<Transform>& transform) { _transform = transform; }

	// Getter and Setter : parent
	weak_ptr<GameObject> GetParent() { return _parent; }
	void SetParent(const shared_ptr<GameObject>& parent);
	void AddChild(const shared_ptr<GameObject>& child) { _children.push_back(child); }
	vector<shared_ptr<GameObject>>& GetChildren() { return _children; }

	// SetActive method
	void SetActive(bool active);
	bool GetActive() { return _isActive; }

	// GameObject state change methods
	void Destroy();
	bool IsPendingDestroy() const { return _pendingDestroy; }

private:
	bool _pendingDestroy = false;
	bool _isActive = true;
	const string _name;
	shared_ptr<Transform> _transform;
	weak_ptr<GameObject> _parent;
	vector<shared_ptr<GameObject>> _children;
	vector<shared_ptr<IComponent>> _components;
	vector<shared_ptr<IRenderable>> _renderables;
	vector<shared_ptr<IBehaviour>> _behaviours;
};

