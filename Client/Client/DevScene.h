#pragma once
#include "Engine\Scene.h"

#pragma region GameObject
class GameObject;
#pragma endregion

#pragma region Components
class Transform;
class Camera;
class Sprite;
class Text;
#pragma endregion

#pragma region Resources
class Shader;
class Texture;
class Font;
#pragma endregion

#pragma region Behaviour
class example;
#pragma endregion

#pragma region Test Scene
class DevScene : public Scene
{
	using Super = Scene;

public:
	DevScene(const string& name);
	virtual ~DevScene() override = default;

protected:
	virtual void CreateSceneContext() override;

// Add GameObjects, Components, Resources here
private:

	// UI Camera
	shared_ptr<Transform> _uiCameraTransform;
	shared_ptr<Camera> _uiCameraComponent;
	shared_ptr<GameObject> _uiCamera;

	// Game Camera
	shared_ptr<Transform> _mainCameraTransform;
	shared_ptr<Camera> _mainCameraComponent;
	shared_ptr<GameObject> _mainCamera;

	// Text UI GameObject
	shared_ptr<Shader> _textShader;
	shared_ptr<Font> _font;
	shared_ptr<Text> _textTexture;
	shared_ptr<Transform> _textTransform;
	shared_ptr<GameObject> _textObject;

	// Sprite GameObject;
	shared_ptr<Shader> _textureShader;
	shared_ptr<Texture> _texture;
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _spriteTransform;
	shared_ptr<example> _sampleScript;
	shared_ptr<GameObject> _spriteObject;
};
#pragma endregion

