#pragma once
#include "Engine\Scene.h"

#pragma region GameObject
class GameObject;
#pragma endregion

#pragma region Components
class Transform;
class Camera;
class Sprite;
class UIText;
class FlipbookPlayer;
class UIButton;
class UICanvas;
class UICheckBox;
#pragma endregion

#pragma region Resources
class RenderPass;
class Shader;
class Texture;
class Font;
class Flipbook;
class Audio;
#pragma endregion

#pragma region Behaviour
class example;
class example1;
class example2;
class example3;
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

#pragma region RENDER_PASSES
	// Local scene shaders
	shared_ptr<Shader> _textShader;
	shared_ptr<Shader> _textureShader;
	shared_ptr<Shader> _instanceShader;

	// UI Camera
	shared_ptr<Transform> _uiCameraTransform;
	shared_ptr<example1> _uiCameraScript;
	shared_ptr<Camera> _uiCameraComponent;
	shared_ptr<GameObject> _uiCamera;

	// Game Camera
	shared_ptr<Transform> _mainCameraTransform;
	shared_ptr<Camera> _mainCameraComponent;
	shared_ptr<GameObject> _mainCamera;

	// Render Passes
	shared_ptr<RenderPass> _uiRenderPass;
	shared_ptr<RenderPass> _textureRenderPass;
	shared_ptr<RenderPass> _instanceRenderPass;
#pragma endregion

	// Text UI GameObject
	shared_ptr<Font> _font;
	shared_ptr<UIText> _textTexture;
	shared_ptr<Transform> _textTransform;
	shared_ptr<GameObject> _textObject;

	// Text UI GameObject2
	shared_ptr<Font> _font2;
	shared_ptr<UIText> _textTexture2;
	shared_ptr<Transform> _textTransform2;
	shared_ptr<GameObject> _textObject2;

	// Sprite GameObject
	shared_ptr<Texture> _texture;
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _spriteTransform;
	shared_ptr<example> _sampleScript;
	shared_ptr<GameObject> _spriteObject;

	// Flipbook GameObject
	shared_ptr<Flipbook> _flipbook;
	shared_ptr<FlipbookPlayer> _flipbookPlayer;
	shared_ptr<Transform> _flipbookTransform;
	shared_ptr<GameObject> _flipbookObject;

	// UI Button
	shared_ptr<Texture> _buttonTexture;
	shared_ptr<Texture> _buttonHoveredTexture;
	shared_ptr<UIButton> _button;
	shared_ptr<Transform> _uiButtonTransform;
	shared_ptr<example2> _sampleScript2;
	shared_ptr<GameObject> _uiButtonObject;

	// UI CheckBox
	shared_ptr<Texture> _checkboxTexture;
	shared_ptr<Texture> _chechboxClicked;
	shared_ptr<UICheckBox> _checkbox;
	shared_ptr<Transform> _uiCheckBoxTransform;
	shared_ptr<example3> _sampleScript3;
	shared_ptr<GameObject> _uiCheckBoxObject;

	// UI Canvas
	shared_ptr<UICanvas> _uiCanvas;
	shared_ptr<Transform> _uiCanvasTransform;
	shared_ptr<GameObject> _uiCanvasObject;
};
#pragma endregion

