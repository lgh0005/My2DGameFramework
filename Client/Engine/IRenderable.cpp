#include "pch.h"
#include "IRenderable.h"
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"

IRenderable::IRenderable(const string& name) : Super(name)
{

}

void IRenderable::Init()
{
    shared_ptr<GameObject> owner;
    if (Utils::IsValidPtr<GameObject>(_owner, owner) == false)
    {
        _model = glm::mat4(1.0f);
        return;
    }

    _ownerTransform = owner->GetTransform();
}

void IRenderable::Update()
{
    _model = _ownerTransform->GetModel();
}
