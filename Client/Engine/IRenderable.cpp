#include "pch.h"
#include "IRenderable.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

IRenderable::IRenderable(const string& name, shared_ptr<Camera> camera) 
    : Super(name), _camera(camera)
{

}

void IRenderable::Update()
{
    if (_owner.expired())
    {
        _model = glm::mat4(1.0f);
        return;
    }

	_model = _owner.lock()->GetTransform()->GetModel();
}
