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
class UniformSet;
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
class House3;
class Building1;
class Building2;
class Building3;
class Bush;
class UISetting;
class Tree1;
class Tree2;
class Player;
class UIPlayerHUD;
#pragma endregion

#pragma region Scripts
class CameraController;
#pragma endregion

class InGame : public Scene
{
	using Super = Scene;

public:
	InGame(const string& name);
	virtual ~InGame() override = default;

protected:
	virtual void CreateSceneContext() override;

#pragma region RENDER_PROPERTIES
private:
	void LoadResources();
	/*=============================
	//    Local scene shaders    //
	=============================*/
	shared_ptr<Shader> _textureShader;
	shared_ptr<Shader> _textShader;
	shared_ptr<Shader> _uiShader;
	shared_ptr<Shader> _playerShader;
	shared_ptr<UniformSet> _playerUniforms;

	/*======================
	//    Game Cameras    //
	======================*/
	// Main Camera
	shared_ptr<Transform> _mainCameraTransform;
	shared_ptr<Camera> _mainCameraComponent;
	shared_ptr<GameObject> _mainCamera;
	shared_ptr<CameraController> _mainCameraController;

	// UI Camera
	shared_ptr<Transform> _uiCameraTransform;
	shared_ptr<Camera> _uiCameraComponent;
	shared_ptr<GameObject> _uiCamera;

	/*=======================
	//    Render Passes    //
	=======================*/
	shared_ptr<RenderPass> _textRenderPass;
	shared_ptr<RenderPass> _textureRenderPass;
	shared_ptr<RenderPass> _uiRenderPass;
	shared_ptr<RenderPass> _playerRenderpass;
#pragma endregion

#pragma region NECESSARY_RESOURCES
private:
	void CreateRenderProperties();

#pragma region BACKGROUND
	// Ground prefab
	shared_ptr<Texture> _groundTexture;
	shared_ptr<Ground> _ground;

	// Background Prefab
	shared_ptr<Texture> _backgroundTexture1;
	shared_ptr<Background1> _background1;

	// Background Prefab
	shared_ptr<Texture> _backgroundTexture2;
	shared_ptr<Background2> _background2;

	// Sidewall Prefab
	shared_ptr<Texture> _sideWallTexture;
	shared_ptr<SideWall> _sideWall;

	// Bush Prefab
	shared_ptr<Texture> _bushTexture;
	shared_ptr<Bush> _bush;

	// House Prefab
	shared_ptr<Texture> _houseTexture2;
	shared_ptr<House2> _house2;
	shared_ptr<Texture> _houseTexture3;
	shared_ptr<House3> _house3;
	shared_ptr<Texture> _buildingTexture1;
	shared_ptr<Building1> _building1;
	shared_ptr<Texture> _buildingTexture2;
	shared_ptr<Building2> _building2;
	shared_ptr<Texture> _buildingTexture3;
	shared_ptr<Building3> _building3;

	// Tree Prefab
	shared_ptr<Texture> _treeTexture1;
	shared_ptr<Tree1> _tree1;
	shared_ptr<Texture> _treeTexture2;
	shared_ptr<Tree2> _tree2;
#pragma endregion

#pragma region PLAYER_FLIPBOOK

#pragma region PLAYER_FLIPBOOK_NORMAL
	shared_ptr<Flipbook> _normal_climb;
	shared_ptr<Flipbook> _normal_combo_1_r;
	shared_ptr<Flipbook> _normal_combo_2_r;
	shared_ptr<Flipbook> _normal_combo_3_r;
	shared_ptr<Flipbook> _normal_damaged_r;
	shared_ptr<Flipbook> _normal_dash_r;
	shared_ptr<Flipbook> _normal_died_r;
	shared_ptr<Flipbook> _normal_fall_r;
	shared_ptr<Flipbook> _normal_idle_r;
	shared_ptr<Flipbook> _normal_jump_r;
	shared_ptr<Flipbook> _normal_run_r;
	shared_ptr<Flipbook> _normal_slide_r;
	shared_ptr<Flipbook> _normal_walk_r;
	shared_ptr<Flipbook> _normal_wallslide_r;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_GUN
	shared_ptr<Flipbook> _gun_climb;
	shared_ptr<Flipbook> _gun_air_attack_r;
	shared_ptr<Flipbook> _gun_damaged_r;
	shared_ptr<Flipbook> _gun_dash_r;
	shared_ptr<Flipbook> _gun_died_r;
	shared_ptr<Flipbook> _gun_idle_r;
	shared_ptr<Flipbook> _gun_jump_r;
	shared_ptr<Flipbook> _gun_run_r;
	shared_ptr<Flipbook> _gun_shot_r;
	shared_ptr<Flipbook> _gun_slide_r;
	shared_ptr<Flipbook> _gun_walk_r;
	shared_ptr<Flipbook> _gun_wallslide_r;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_SWORD
	shared_ptr<Flipbook> _sword_climb;
	shared_ptr<Flipbook> _sword_air_attack_r;
	shared_ptr<Flipbook> _sword_combo_1_r;
	shared_ptr<Flipbook> _sword_combo_2_r;
	shared_ptr<Flipbook> _sword_combo_3_r;
	shared_ptr<Flipbook> _sword_damaged_r;
	shared_ptr<Flipbook> _sword_dash_r;
	shared_ptr<Flipbook> _sword_died_r;
	shared_ptr<Flipbook> _sword_idle_r;
	shared_ptr<Flipbook> _sword_jump_r;
	shared_ptr<Flipbook> _sword_run_r;
	shared_ptr<Flipbook> _sword_slide_r;
	shared_ptr<Flipbook> _sword_walk_r;
	shared_ptr<Flipbook> _sword_wallslide_r;
#pragma endregion

#pragma endregion

#pragma region MAIN_UI
	shared_ptr<Texture> _healthTexture;
	shared_ptr<Sprite> _healthSprite;

	shared_ptr<GameObject> _healthObject1;
	shared_ptr<Transform> _healthTransform1;
	shared_ptr<Sprite> _healthSprite1;

	shared_ptr<GameObject> _healthObject2;
	shared_ptr<Transform> _healthTransform2;
	shared_ptr<Sprite> _healthSprite2;

	shared_ptr<GameObject> _healthObject3;
	shared_ptr<Transform> _healthTransform3;
	shared_ptr<Sprite> _healthSprite3;

	shared_ptr<Font> _scoreText;
	shared_ptr<Font> _noWeaponText;
	array<shared_ptr<Font>, 11> _numberText;



#pragma endregion

#pragma region SCENE_CONTEXT
	shared_ptr<Player> _player;
	shared_ptr<UIPlayerHUD> _mainHUD;
#pragma endregion
};

