#pragma once
#include "IComponent.h"

class BoxCollider : public IComponent
{
	using Super = IComponent;
	using CollisionEnterCallBack = function<void(const shared_ptr<BoxCollider>&)>;
	using CollisionExitCallBack = function<void(const shared_ptr<BoxCollider>&)>;

public:
	BoxCollider(const string& name, const glm::vec2& size, const glm::vec2& offset = glm::vec2(0.0f));
	virtual ~BoxCollider() override = default;

public:
	virtual void Init() override;
	bool CheckCollision(const shared_ptr<BoxCollider>& other);
	void OnCollisionEnter(const shared_ptr<BoxCollider>& other);
	void OnCollisionExit(const shared_ptr<BoxCollider>& other);

public:
	void SetSize(const glm::vec2& size) { _size = size; }
	glm::vec2 GetSize() { return _size; }
	void SetOffset(const glm::vec2& offset) { _offset = offset; }
	glm::vec2 GetOffset() { return _offset; }

public:
	void SetLayer(CollisionLayer::Layers layer) { _layer = layer; }
	CollisionLayer::Layers GetLayer() const { return _layer; }
	void SetMask(CollisionLayer::Layers mask) { _mask = mask; }
	CollisionLayer::Layers GetMask() const { return _mask; }

public:
	void SetCollisionEnterCallback(CollisionEnterCallBack callback) { _collisionEnterEvent = callback; }
	void SetCollisionExitCallback(CollisionExitCallBack callback) { _collisionExitEvent = callback; }
	void ClearCollisionEnterCallback() { _collisionEnterEvent = nullptr; }
	void ClearCollisionExitCallback() { _collisionExitEvent = nullptr; }

private:
	CollisionEnterCallBack _collisionEnterEvent;
	CollisionExitCallBack _collisionExitEvent;

private:
	CollisionLayer::Layers _layer = CollisionLayer::Layers::None;
	CollisionLayer::Layers _mask = CollisionLayer::Layers::All;
	shared_ptr<Transform> _ownerTransform;
	glm::vec2 _size;
	glm::vec2 _offset;
};
