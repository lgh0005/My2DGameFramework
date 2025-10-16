#pragma once
#include "IComponent.h"

enum class CollisionState
{
	None,
	Exit,
	Enter,
};

class BoxCollider : public IComponent
{
	using Super = IComponent;
	using CollisionEnterCallBack = function<void(const shared_ptr<BoxCollider>&)>;
	using CollisionExitCallBack = function<void(const shared_ptr<BoxCollider>&)>;

public:
	BoxCollider(const string& name, const glm::vec2& size);
	virtual ~BoxCollider() override = default;

public:
	virtual void Init() override;
	bool CheckCollision(const shared_ptr<BoxCollider>& other);
	void OnCollisionEnter(const shared_ptr<BoxCollider>& other);
	void OnCollisionExit(const shared_ptr<BoxCollider>& other);

public:
	glm::vec2 GetSize() { return _size; }
	void SetCollisionEnterCallback(CollisionEnterCallBack callback) { _collisionEnterEvent = callback; }
	void SetCollisionExitCallback(CollisionExitCallBack callback) { _collisionExitEvent = callback; }
	void SetCollisionState(const CollisionState& state) { _state = state; }
	void ClearCollisionEnterCallback() { _collisionEnterEvent = nullptr; }
	void ClearCollisionExitCallback() { _collisionExitEvent = nullptr; }

private:
	CollisionState _state = CollisionState::None;
	CollisionEnterCallBack _collisionEnterEvent;
	CollisionExitCallBack _collisionExitEvent;

private:
	shared_ptr<Transform> _ownerTransform;
	glm::vec2 _size;
};
