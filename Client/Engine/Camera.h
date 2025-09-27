#pragma once
#include "IComponent.h"

class Camera : public IComponent
{
	using Super = IComponent;

public:
	Camera(const string& name);
	virtual ~Camera() override;

public:
	virtual void Awake(const shared_ptr<GameObject>& owner) override;
	virtual void Update() override;

public:
	void SetView(glm::mat4& view) { _view = view; _dirty = true; }
	glm::mat4& GetView() { return _view; }
	void SetProjection(glm::mat4& projection) { _projection = projection; _dirty = true; }
	glm::mat4& GetProjection() { return _projection; }
	glm::mat4& GetInvVP();

private:
	glm::mat4 _view;
	glm::mat4 _projection;

	bool _dirty = false;
	glm::mat4 _invVP;

	glm::vec3 _lastPos;
	glm::vec3 _lastRot;
	glm::vec3 _lastScale;
};

