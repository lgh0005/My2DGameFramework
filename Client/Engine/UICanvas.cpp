#include "pch.h"
#include "UICanvas.h"
#include "UIGrid.h"
#include "Camera.h"

UICanvas::UICanvas(const string& name, const glm::vec2& size, shared_ptr<UIGrid> grid)
	: Super(name, size), _grid(grid)
{
}

void UICanvas::Update()
{
	Super::Update();
}

void UICanvas::UpdateLayout()
{
	if (_grid) _grid->Arrange(_uis, _size);
}