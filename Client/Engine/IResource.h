#pragma once

class IComponent;

class IResource : public enable_shared_from_this<IResource>
{
public:
	IResource(const string& name);
	virtual ~IResource();

public:
	virtual void Init() abstract;

protected:
	const string _name;
	weak_ptr<IComponent> _owner;
};

