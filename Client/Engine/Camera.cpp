#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

Camera::Camera(const string& name) : Super(name), _view(glm::mat4(1.0f)), _projection(glm::mat4(1.0f))
{
}

Camera::~Camera()
{
}

void Camera::Init(shared_ptr<GameObject> owner)
{
	Super::Init(owner);
	
	_view = glm::mat4(1.0f);
    _projection = glm::ortho
    (
        -(float)WindowConfig::GWinSizeX / 2.0f, (float)WindowConfig::GWinSizeX / 2.0f,   // left, right
        -(float)WindowConfig::GWinSizeY / 2.0f, (float)WindowConfig::GWinSizeY / 2.0f,   // bottom, top
        -1.0f, 1.0f                                                                      // near, far
    );
}

void Camera::Update()
{
    if (auto owner = _owner.lock())
    {
        glm::vec3 pos = owner->GetTransform()->GetPosition();
        glm::vec3 rot = owner->GetTransform()->GetRotation();

        _view = glm::translate(glm::mat4(1.0f), -pos);
    }
}
