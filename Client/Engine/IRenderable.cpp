#include "pch.h"
#include "IRenderable.h"
#include "GameObject.h"
#include "Transform.h"

IRenderable::IRenderable(const string& name) : Super(name)
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
