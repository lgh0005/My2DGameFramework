#include "pch.h"
#include "IRenderable.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

IRenderable::IRenderable(const string& name, shared_ptr<Camera> camera) 
    : Super(name), _camera(camera)
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
