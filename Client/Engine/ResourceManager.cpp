#include "pch.h"
#include "ResourceManager.h"
#include "IResource.h"

void ResourceManager::Init()
{

}

void ResourceManager::Update()
{

}

void ResourceManager::AddResource(shared_ptr<IResource> resource)
{
	_resources[resource->GetName()] = resource;
}

void ResourceManager::Release()
{
	_resources.clear();
}
