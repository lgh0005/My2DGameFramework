#include "pch.h"
#include "IUIInteractable.h"

IUIInteractable::IUIInteractable(const string& name, const glm::vec2& size)
	: Super(name, size)
{

}

IUIInteractable::~IUIInteractable()
{
}


bool IUIInteractable::IsMouseHovered(const glm::vec2& mousePos)
{
    glm::vec2 pos = GetWorldPosition();
    glm::vec2 size = GetWorldSize();

    return (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
        mousePos.y >= pos.y && mousePos.y <= pos.y + size.y);
}