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
class BGM;
class SFX;
#pragma endregion

#pragma region Prefabs
class Ground;
#pragma endregion


class Lobby : public Scene
{
	using Super = Scene;

public:
	Lobby(const string& name);
	virtual ~Lobby() override = default;

protected:
	virtual void CreateSceneContext() override;

#pragma region RENDER_PROPERTIES
private:

	void CreateRenderProperties();

	/*=============================
	//    Local scene shaders    //
	=============================*/
	shared_ptr<Shader> _textureShader;
	shared_ptr<Shader> _textShader;

	/*======================
	//    Game Cameras    //
	======================*/
	// Main Camera
	shared_ptr<Transform> _mainCameraTransform;
	shared_ptr<Camera> _mainCameraComponent;
	shared_ptr<GameObject> _mainCamera;

	// UI Camera
	shared_ptr<Transform> _uiCameraTransform;
	shared_ptr<Camera> _uiCameraComponent;
	shared_ptr<GameObject> _uiCamera;

	/*=======================
	//    Render Passes    //
	=======================*/
	shared_ptr<RenderPass> _uiRenderPass;
	shared_ptr<RenderPass> _textureRenderPass;
#pragma endregion

#pragma region GAME_OBJECTS_AND_PREFABS
	
	void LoadResources();

	// Ground prefab
	shared_ptr<Texture> _groundTexture;
	shared_ptr<Ground> _ground;

#pragma endregion

private:
};

