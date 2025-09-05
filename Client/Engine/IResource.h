#pragma once

class IResource : public enable_shared_from_this<IResource>
{
public:
	IResource(const string& name);
	virtual ~IResource();

public:
	virtual void Init();

public:
	const string& GetName() { return _name; }

protected:
	const string _name;
};

