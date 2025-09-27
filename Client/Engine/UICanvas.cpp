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

	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner))
	{
		for (auto& ui : _uis)
		{
			ui->Init();
			
			shared_ptr<GameObject> child;
			if (Utils::IsValidPtr(ui->GetOwner(), child))
			{
				child->SetParent(owner);
				child->GetTransform()->Init();
			}
		}
	}
}

void UICanvas::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	for (auto& ui : _uis) 
		ui->Render(shader, model, camera);
}

void UICanvas::AddUIComponent(shared_ptr<IUIElement> ui)
{
	_uis.push_back(ui);
}

void UICanvas::RemoveUIComponent(shared_ptr<IUIElement> ui)
{
	_uis.erase(remove(_uis.begin(), _uis.end(), ui), _uis.end());
}
