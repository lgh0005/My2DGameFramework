#include "pch.h"
#include "UICanvas.h"
#include "GameObject.h"
#include "Transform.h"

UICanvas::UICanvas(const string& name, shared_ptr<Camera> camera, const glm::vec2& size)
	: Super(name, camera, size)
{

}

void UICanvas::Init()
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

void UICanvas::Render()
{
	for (auto& ui : _uis) ui->Render();
}

void UICanvas::AddUIComponent(shared_ptr<IUIElement> ui)
{
	_uis.push_back(ui);
}

void UICanvas::RemoveUIComponent(shared_ptr<IUIElement> ui)
{
	_uis.erase(remove(_uis.begin(), _uis.end(), ui), _uis.end());
}
