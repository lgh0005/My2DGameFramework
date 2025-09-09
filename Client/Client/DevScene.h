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
class FlipbookPlayer;
#pragma endregion

#pragma region Resources
class Shader;
class Texture;
class Font;
class Flipbook;
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

	// Local scene shaders
	shared_ptr<Shader> _textShader;
	shared_ptr<Shader> _textureShader;

	// UI Camera
	shared_ptr<Transform> _uiCameraTransform;
	shared_ptr<Camera> _uiCameraComponent;
	shared_ptr<GameObject> _uiCamera;

	// Game Camera
	shared_ptr<Transform> _mainCameraTransform;
	shared_ptr<Camera> _mainCameraComponent;
	shared_ptr<GameObject> _mainCamera;

	// Text UI GameObject
	shared_ptr<Font> _font;
	shared_ptr<Text> _textTexture;
	shared_ptr<Transform> _textTransform;
	shared_ptr<GameObject> _textObject;

	// Sprite GameObject;
	shared_ptr<Texture> _texture;
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _spriteTransform;
	shared_ptr<example> _sampleScript;
	shared_ptr<GameObject> _spriteObject;

	// Flipbook GameObject;
	shared_ptr<Flipbook> _flipbook;
	shared_ptr<FlipbookPlayer> _flipbookPlayer;
	shared_ptr<Transform> _flipbookTransform;
	shared_ptr<GameObject> _flipbookObject;
};
#pragma endregion

