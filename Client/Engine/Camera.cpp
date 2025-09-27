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

void Camera::Awake(const shared_ptr<GameObject>& owner)
{
	Super::Awake(owner);
	
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
        auto transform = owner->GetTransform();
        glm::vec3 pos = transform->GetPosition();
        glm::vec3 rot = transform->GetRotation();
        glm::vec3 scl = transform->GetScale();

        if (pos != _lastPos || rot != _lastRot || scl != _lastScale)
        {
            glm::mat4 view(1.0f);
            view = glm::translate(view, -pos);
            view = glm::rotate(view, glm::radians(-rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
            view = glm::scale(view, glm::vec3(1.0f / scl.x, 1.0f / scl.y, 1.0f));
            
            _view = view;
            _dirty = true;

            _lastPos = pos;
            _lastRot = rot;
            _lastScale = scl;
        }
    }
}

glm::mat4& Camera::GetInvVP()
{
    if (_dirty)
    {
        _invVP = glm::inverse(_projection * _view);
        _dirty = false;
    }
    return _invVP;
}