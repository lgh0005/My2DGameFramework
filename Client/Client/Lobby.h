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
class UniformSet;
class Shader;
class Texture;
class Font;
class Flipbook;
class BGM;
class SFX;
#pragma endregion

#pragma region Prefabs
class Ground;
class Background1;
class Background2;
class Character;
class SideWall;
class House1;
class House2;
class Bush;
class UISetting;
class ColliderDebuger;
#pragma endregion

#pragma region Scripts
class CharacterController;
class UIBlocker;
class StartButtonScript;
class OptionButtonScript;
class QuitButtonScript;
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
	shared_ptr<Shader> _SettingUIShader;

	shared_ptr<Shader> _CharacterShader;
	shared_ptr<UniformSet> _CharacterUniforms;

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
	shared_ptr<RenderPass> _CharacterRenderPass;
	shared_ptr<RenderPass> _SettingUIRenderPass;
#pragma endregion

#pragma region NECESSARY_RESOURCES

	void LoadResources();

	// Ground prefab
	shared_ptr<Texture> _groundTexture;
	shared_ptr<Ground> _ground;

	// Background Prefab
	shared_ptr<Texture> _backgroundTexture1;
	shared_ptr<Background1> _background1;

	// Background Prefab
	shared_ptr<Texture> _backgroundTexture2;
	shared_ptr<Background2> _background2;

	// Character Prefab
	shared_ptr<Character> _character;
	shared_ptr<Flipbook> _characterIdleLeftFlipbook;
	shared_ptr<Flipbook> _characterIdleRightFlipbook;
	shared_ptr<Flipbook> _characterWalkLeftFlipbook;
	shared_ptr<Flipbook> _characterWalkRightFlipbook;

	// Sidewall Prefab
	shared_ptr<Texture> _sideWallTexture;
	shared_ptr<SideWall> _sideWall;

	// Bush Prefab
	shared_ptr<Texture> _bushTexture;
	shared_ptr<Bush> _bush;
		
	// House Prefab
	shared_ptr<Texture> _houseTexture1;
	shared_ptr<House1> _house1;
	shared_ptr<Texture> _houseTexture2;
	shared_ptr<House2> _house2;

	// BGM
	shared_ptr<BGM> _lobbyBGM;

	// SFX
	shared_ptr<SFX> _lobbySFX;

	// Settings UI
	shared_ptr<Texture> _uiPanel;
	shared_ptr<Texture> _uiToggle;
	shared_ptr<Texture> _uiToggleSelected;
	shared_ptr<Texture> _checkIcon;
	shared_ptr<Texture> _backIcon;
	shared_ptr<Font> _bgmText;
	shared_ptr<Font> _sfxText;

#pragma region MainUI
	shared_ptr<UICanvas> _uiCanvas;
	shared_ptr<Transform> _uiCanvasTransform;
	shared_ptr<GameObject> _uiCanvasObject;

	shared_ptr<Font> _gameTitleText1;
	shared_ptr<UIText> _gameTitleTextTexture1;
	shared_ptr<Transform> _gameTitleTextTransform1;
	shared_ptr<GameObject> _gameTitleGameObject1;

	shared_ptr<Font> _gameTitleText2;
	shared_ptr<UIText> _gameTitleTextTexture2;
	shared_ptr<Transform> _gameTitleTextTransform2;
	shared_ptr<GameObject> _gameTitleGameObject2;

	shared_ptr<Texture> _buttonTextureNormal;
	shared_ptr<Texture> _buttonTextureSelect;

	shared_ptr<UIButton> _button1;
	shared_ptr<Transform> _buttonTransform1;
	shared_ptr<GameObject> _buttonGameObject1;
	shared_ptr<Font> _buttonText1;
	shared_ptr<UIText> _buttonText1Texture;
	shared_ptr<StartButtonScript> _buttonScript1;

	shared_ptr<UIButton> _button2;
	shared_ptr<Transform> _buttonTransform2;
	shared_ptr<GameObject> _buttonGameObject2;
	shared_ptr<Font> _buttonText2;
	shared_ptr<UIText> _buttonText2Texture;
	shared_ptr<OptionButtonScript> _buttonScript2;

	shared_ptr<UIButton> _button3;
	shared_ptr<Transform> _buttonTransform3;
	shared_ptr<GameObject> _buttonGameObject3;
	shared_ptr<Font> _buttonText3;
	shared_ptr<UIText> _buttonText3Texture;
	shared_ptr<QuitButtonScript> _buttonScript3;

	shared_ptr<GameObject> _uiBlocker;
	shared_ptr<Transform> _uiBlockerTransform;
	shared_ptr<UIBlocker> _uiBlockerScript;

#pragma endregion

#pragma region SettingUI
	shared_ptr<UISetting> _settingUI;
#pragma endregion

#pragma endregion
};

