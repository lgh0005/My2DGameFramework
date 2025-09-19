#include "pch.h"
#include "IUIContainer.h"
#include "GameObject.h"
#include "Transform.h"

IUIContainer::IUIContainer(const string& name, const glm::vec2& size)
	: Super(name, size)
{
}

void IUIContainer::Init()
{ 
	Super::Init();

	auto owner = _owner.lock();
	for (auto& ui : _uis)
	{
		ui->Init();
		auto childObj = ui->GetOwner();
		if (childObj)
		{
			childObj->SetParent(owner);
			childObj->GetTransform()->Init();
		}
	}
}

void IUIContainer::Render(const shared_ptr<Camera>& camera)
{
	for (auto& ui : _uis) ui->Render(camera);
}

void IUIContainer::AddUIComponent(shared_ptr<IUIElement> ui)
{
	_uis.push_back(ui);
}

void IUIContainer::RemoveUIComponent(shared_ptr<IUIElement> ui)
{
	_uis.erase(remove(_uis.begin(), _uis.end(), ui), _uis.end());
}
