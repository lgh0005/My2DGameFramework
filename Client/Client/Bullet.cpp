#include "pch.h"
#include "Bullet.h"

#pragma region SCRIPT
#include "BulletController.h"
#include "BulletCollideScript.h"
#pragma endregion

Bullet::Bullet(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Bullet::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;
	auto& GameObjectList = scene->GetGameObjectList();

	// bullet
	{
		_bullet = make_shared<GameObject>(name);
		_bulletTransform = make_shared<Transform>(name, position, rotation, scale);
		_bullet->SetTransform(_bulletTransform);
	}

	// sprite
	{
		auto sprite = make_shared<Sprite>("BulletSprite", RESOURCE.GetResource<Texture>("BulletTexture"));
		_bullet->AddRenderable(sprite);
		shared_ptr<RenderPass> renderPass = scene->GetRenderPass("_bulletRenderPass");
		auto renderable = _bullet->GetRenderable("BulletSprite");
		renderPass->AddRenderable(renderable);
	}

	// DEBUG
	{
		auto testSprite = make_shared<Sprite>("TestSprite3", RESOURCE.GetResource<Texture>("TEST1"));
		_bullet->AddRenderable(testSprite);
		shared_ptr<RenderPass> renderPass = scene->GetRenderPass("_debugRenderPass");
		auto renderable = _bullet->GetRenderable("TestSprite3");
		renderPass->AddRenderable(renderable);
	}

	// Collider
	{
		shared_ptr<BoxCollider> bulletCollider = make_shared<BoxCollider>("BulletCollider", glm::vec2(1.0f, 1.0f));
		_bullet->AddComponent(bulletCollider);
	}

	// script
	{
		shared_ptr<BulletController> script = make_shared<BulletController>("BulletController");
		_bullet->AddBehaviour(script);
	}

	return _bullet;
}
