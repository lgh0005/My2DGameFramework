#pragma once
#include "Engine\Scene.h"

#pragma region GameObject
class GameObject;
#pragma endregion

#pragma region Components
class Transform;
class Camera;
class Sprite;
#pragma endregion

#pragma region Resources
class RenderPass;
class Shader;
class Texture;
class BGM;
class SFX;
#pragma endregion

class TestScene : public Scene
{
	using Super = Scene;

public:
	TestScene(const string& name);
	virtual ~TestScene() override = default;

protected:
	virtual void CreateSceneContext() override;

private:
#pragma region RENDER_PASSES
	// Shader
	shared_ptr<Shader> _textureShader;

	// Game Camera
	shared_ptr<Transform> _mainCameraTransform;
	shared_ptr<Camera> _mainCameraComponent;
	shared_ptr<GameObject> _mainCamera;

	// Render Pass
	shared_ptr<RenderPass> _textureRenderPass;
#pragma endregion

	// Sprite GameObject
	shared_ptr<Texture> _texture;
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _spriteTransform;
	shared_ptr<GameObject> _spriteObject;
};

