#pragma once
#include "ISingleton.h"

class IResource;

class ResourceManager : public ISingleton<ResourceManager>
{
	DECLARE_SINGLE(ResourceManager);

public:
	virtual ~ResourceManager() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void AddResource(shared_ptr<IResource> resource);

	template<typename T>
	shared_ptr<T> GetResource(const string& resourceName)
	{
		auto it = _resources.find(resourceName);
		if (it != _resources.end()) return dynamic_pointer_cast<T>(it->second);
		return nullptr;
	}

	void Release();

private:
	unordered_map<string, shared_ptr<IResource>> _resources;
};

