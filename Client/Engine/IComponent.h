#pragma once

class GameObject;

class IComponent : public enable_shared_from_this<IComponent>
{
public:
	IComponent(const string& name);
	virtual ~IComponent() = default;

public:
	virtual void Awake(shared_ptr<GameObject> owner);
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void LateUpdate();

public:
	const string& GetName() { return _name; }
	shared_ptr<GameObject> GetOwner() { return _owner.lock(); }

protected:
	const string _name;
	weak_ptr<GameObject> _owner;
};

