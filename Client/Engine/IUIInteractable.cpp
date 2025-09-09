#include "pch.h"
#include "IUIInteractable.h"

IUIInteractable::IUIInteractable(const string& name, const glm::vec2& size)
	: Super(name, size)
{

}

bool IUIInteractable::OnHovered(const glm::vec2& mousePos)
{
    glm::vec2 pos = GetWorldPosition();
    glm::vec2 size = GetWorldSize();

    return (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
        mousePos.y >= pos.y && mousePos.y <= pos.y + size.y);
}

bool IUIInteractable::OnClicked(const glm::vec2& mousePos, Inputs::Mouse input)
{
    if (OnHovered(mousePos) == false) return false;
    return INPUT.MouseClick(input);
}

bool IUIInteractable::OnHold(const glm::vec2& mousePos, Inputs::Mouse input)
{
    if (OnHovered(mousePos) == false) return false;
    return INPUT.MouseHold(input);
}
