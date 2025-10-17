#pragma once

class GameObject;

class IComponent : public enable_shared_from_this<IComponent>
{
public:
	IComponent(const string& name);
	virtual ~IComponent() = default;

public:
	virtual void Awake(const shared_ptr<GameObject>& owner);
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void LateUpdate();

public:
	const string& GetName() { return _name; }
	weak_ptr<GameObject> GetOwner() { return _owner; }

public:
	void SetActive(bool active) { _isActive = active; }
	bool IsActive() { return _isActive; }
	void Destroy() { _pendingDestroy = true; }
	bool IsPendingDestroy() const { return _pendingDestroy; }

public:
	template<typename T>
	shared_ptr<T> GetSelf()
	{
		return static_pointer_cast<T>(shared_from_this());
	}

protected:
	bool _pendingDestroy = false;
	bool _isActive = true;
	const string _name;
	weak_ptr<GameObject> _owner;
};

