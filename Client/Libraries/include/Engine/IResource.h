#pragma once

class IResource : public enable_shared_from_this<IResource>
{
public:
	IResource(const string& name);
	virtual ~IResource() = default;

public:
	virtual void Init();
	virtual void Update();

public:
	const string& GetName() { return _name; }

protected:
	const string _name;
};

