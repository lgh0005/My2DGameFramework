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
	shared_ptr<RenderPass> _uiRenderPass;
	shared_ptr<RenderPass> _textureRenderPass;

#pragma endregion

#pragma region NECESSARY_RESOURCES
private:
	void CreateRenderProperties();

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
	shared_ptr<Texture> _houseTexture1;
	shared_ptr<House1> _house1;
	shared_ptr<Texture> _houseTexture2;
	shared_ptr<House2> _house2;

#pragma region PLAYER_FLIPBOOK

#pragma region PLAYER_FLIPBOOK_NORMAL
	shared_ptr<Flipbook> _normal_climb;
	shared_ptr<Flipbook> _normal_combo_1_r;
	shared_ptr<Flipbook> _normal_combo_1_l;
	shared_ptr<Flipbook> _normal_combo_2_r;
	shared_ptr<Flipbook> _normal_combo_2_l;
	shared_ptr<Flipbook> _normal_combo_3_r;
	shared_ptr<Flipbook> _normal_combo_3_l;
	shared_ptr<Flipbook> _normal_damaged_r;
	shared_ptr<Flipbook> _normal_damaged_l;
	shared_ptr<Flipbook> _normal_dash_r;
	shared_ptr<Flipbook> _normal_dash_l;
	shared_ptr<Flipbook> _normal_died_r;
	shared_ptr<Flipbook> _normal_died_l;
	shared_ptr<Flipbook> _normal_fall_r;
	shared_ptr<Flipbook> _normal_fall_l;
	shared_ptr<Flipbook> _normal_idle_r;
	shared_ptr<Flipbook> _normal_idle_l;
	shared_ptr<Flipbook> _normal_jump_r;
	shared_ptr<Flipbook> _normal_jump_l;
	shared_ptr<Flipbook> _normal_run_r;
	shared_ptr<Flipbook> _normal_run_l;
	shared_ptr<Flipbook> _normal_slide_r;
	shared_ptr<Flipbook> _normal_slide_l;
	shared_ptr<Flipbook> _normal_walk_r;
	shared_ptr<Flipbook> _normal_walk_l;
	shared_ptr<Flipbook> _normal_wallslide_r;
	shared_ptr<Flipbook> _normal_wallslide_l;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_GUN
	shared_ptr<Flipbook> _gun_climb;
	shared_ptr<Flipbook> _gun_air_attack_r;
	shared_ptr<Flipbook> _gun_air_attack_l;
	shared_ptr<Flipbook> _gun_damaged_r;
	shared_ptr<Flipbook> _gun_damaged_l;
	shared_ptr<Flipbook> _gun_dash_r;
	shared_ptr<Flipbook> _gun_dash_l;
	shared_ptr<Flipbook> _gun_died_r;
	shared_ptr<Flipbook> _gun_died_l;
	shared_ptr<Flipbook> _gun_idle_r;
	shared_ptr<Flipbook> _gun_idle_l;
	shared_ptr<Flipbook> _gun_jump_r;
	shared_ptr<Flipbook> _gun_jump_l;
	shared_ptr<Flipbook> _gun_run_r;
	shared_ptr<Flipbook> _gun_run_l;
	shared_ptr<Flipbook> _gun_shot_r;
	shared_ptr<Flipbook> _gun_shot_l;
	shared_ptr<Flipbook> _gun_slide_r;
	shared_ptr<Flipbook> _gun_slide_l;
	shared_ptr<Flipbook> _gun_walk_r;
	shared_ptr<Flipbook> _gun_walk_l;
	shared_ptr<Flipbook> _gun_wallslide_r;
	shared_ptr<Flipbook> _gun_wallslide_l;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_SWORD
	shared_ptr<Flipbook> _sword_climb;
	shared_ptr<Flipbook> _sword_air_attack_r;
	shared_ptr<Flipbook> _sword_air_attack_l;
	shared_ptr<Flipbook> _sword_combo_1_r;
	shared_ptr<Flipbook> _sword_combo_1_l;
	shared_ptr<Flipbook> _sword_combo_2_r;
	shared_ptr<Flipbook> _sword_combo_2_l;
	shared_ptr<Flipbook> _sword_combo_3_r;
	shared_ptr<Flipbook> _sword_combo_3_l;
	shared_ptr<Flipbook> _sword_damaged_r;
	shared_ptr<Flipbook> _sword_damaged_l;
	shared_ptr<Flipbook> _sword_dash_r;
	shared_ptr<Flipbook> _sword_dash_l;
	shared_ptr<Flipbook> _sword_died_r;
	shared_ptr<Flipbook> _sword_died_l;
	shared_ptr<Flipbook> _sword_idle_r;
	shared_ptr<Flipbook> _sword_idle_l;
	shared_ptr<Flipbook> _sword_jump_r;
	shared_ptr<Flipbook> _sword_jump_l;
	shared_ptr<Flipbook> _sword_run_r;
	shared_ptr<Flipbook> _sword_run_l;
	shared_ptr<Flipbook> _sword_slide_r;
	shared_ptr<Flipbook> _sword_slide_l;
	shared_ptr<Flipbook> _sword_walk_r;
	shared_ptr<Flipbook> _sword_walk_l;
	shared_ptr<Flipbook> _sword_wallslide_r;
	shared_ptr<Flipbook> _sword_wallslide_l;
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region SCENE_CONTEXT
	shared_ptr<GameObject> _player;
	shared_ptr<Transform> _playerTransform;
#pragma endregion
};

