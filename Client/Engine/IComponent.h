#pragma once

class GameObject;

class IComponent : public enable_shared_from_this<IComponent>
{
public:
	IComponent(const string& name);
	virtual ~IComponent();

public:
	virtual void Init(shared_ptr<GameObject> owner);
	virtual void Update();

public:
	const string& GetName() { return _name; }
	shared_ptr<GameObject> GetOwner() { return _owner.lock(); }

private:
	const string _name;
	weak_ptr<GameObject> _owner;
};

