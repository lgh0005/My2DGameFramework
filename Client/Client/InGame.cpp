#include "pch.h"
#include "InGame.h"

#pragma region Prefabs
#include "Ground.h"
#include "Background1.h"
#include "Background2.h"
#include "Character.h"
#include "SideWall.h"
#include "House1.h"
#include "House2.h"
#include "House3.h"
#include "Building1.h"
#include "Building2.h"
#include "Building3.h"
#include "Bush.h"
#include "UISetting.h"
#include "Tree1.h"
#include "Tree2.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UIPlayerHUD.h"
#include "UIPlayerHealth.h"
#pragma endregion

#pragma region Scripts
#include "CameraController.h"
#pragma endregion

#pragma region FOR_DEBUG
#include "ColliderDebuger.h";
#pragma endregion

InGame::InGame(const string& name) : Super(name)
{

}

void InGame::CreateRenderProperties() 
{
	/*=================
	//    Shaders    //
	=================*/
	shared_ptr<Shader> _textureShader = make_shared<Shader>("TextureShader", "../Resources/Shaders/default.vert", "../Resources/Shaders/default.frag");
	_textureShader->Init();
	_textureShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_textureShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_textureShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_textureShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	RESOURCE.AddResource(_textureShader);

	shared_ptr<Shader> _textShader = make_shared<Shader>("TextShader", "../Resources/Shaders/text.vert", "../Resources/Shaders/text.frag");
	_textShader->Init();
	_textShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_textShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_textShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_textShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	_textShader->AddUniform(Uniforms::UNIFORM_COLOR);
	RESOURCE.AddResource(_textShader);

	shared_ptr<Shader> _playerShader = make_shared<Shader>("PlayerShader", "../Resources/Shaders/Character.vert", "../Resources/Shaders/Character.frag");
	_playerShader->Init();
	_playerShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_playerShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_playerShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_playerShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	_playerShader->AddUniform("flip");
	RESOURCE.AddResource(_playerShader);
	shared_ptr<UniformSet> _playerUniforms = make_shared<UniformSet>("PlayerUniforms");
	_playerUniforms->Set("flip", false);
	RESOURCE.AddResource(_playerUniforms);

	shared_ptr<Shader> _enemyShader = make_shared<Shader>("EnemyShader", "../Resources/Shaders/Enemy.vert", "../Resources/Shaders/Enemy.frag");
	_enemyShader->Init();
	_enemyShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_enemyShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_enemyShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_enemyShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	_enemyShader->AddUniform("flip");
	RESOURCE.AddResource(_enemyShader);
	shared_ptr<UniformSet> _enemyUniforms = make_shared<UniformSet>("EnemyUniforms");
	_enemyUniforms->Set("flip", false);
	RESOURCE.AddResource(_enemyUniforms);

	shared_ptr<Shader> _bulletShader = make_shared<Shader>("BulletShader", "../Resources/Shaders/bullet.vert", "../Resources/Shaders/bullet.frag");
	_bulletShader->Init();
	_bulletShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_bulletShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_bulletShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_bulletShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	_bulletShader->AddUniform("flip");
	RESOURCE.AddResource(_bulletShader);
	shared_ptr<UniformSet> _bulletUniforms = make_shared<UniformSet>("BulletUniforms");
	_bulletUniforms->Set("flip", false);
	RESOURCE.AddResource(_bulletUniforms);

	shared_ptr<Shader> _uiShader = make_shared<Shader>("UIShader", "../Resources/Shaders/hud.vert", "../Resources/Shaders/hud.frag");
	_uiShader->Init();
	_uiShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_uiShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_uiShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_uiShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	RESOURCE.AddResource(_uiShader);

	/* FOR DEBUG */
	shared_ptr<Shader> _debugShader = make_shared<Shader>("DEBUG", "../Resources/Shaders/debug.vert", "../Resources/Shaders/debug.frag");
	_debugShader->Init();
	_debugShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_debugShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_debugShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_debugShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	RESOURCE.AddResource(_debugShader);

	/*=================
	//    Cameras    //
	=================*/
	// Main Camera
	shared_ptr<Camera> _mainCameraComponent = make_shared<Camera>("MainCameraComponent");
	shared_ptr<GameObject> _mainCamera = make_shared<GameObject>("MainCamera");
	_mainCamera->AddComponent(_mainCameraComponent);
	shared_ptr<Transform> _mainCameraTransform = make_shared<Transform>
		(
			"MainCameraTransform",
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
	_mainCamera->SetTransform(_mainCameraTransform);
	shared_ptr<CameraController> _mainCameraController = make_shared<CameraController>("CameraController");
	_mainCamera->AddBehaviour(_mainCameraController);
	_gameObjects.push_back(_mainCamera);

	// Load UI camera
	shared_ptr<Camera> _uiCameraComponent = make_shared<Camera>("UICameraComponent");
	shared_ptr<GameObject> _uiCamera = make_shared<GameObject>("UICamera");
	_uiCamera->AddComponent(_uiCameraComponent);
	shared_ptr<Transform> _uiCameraTransform = make_shared<Transform>
		(
			"UICameraTransform",
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
	_uiCamera->SetTransform(_uiCameraTransform);
	_gameObjects.push_back(_uiCamera);

	/*=======================
	//    Render Passes    //
	=======================*/
	shared_ptr<RenderPass> _textRenderPass = make_shared<RenderPass>();
	_textRenderPass->SetShader(_textShader);
	_textRenderPass->SetCamera(_uiCameraComponent);
	AddRenderPass("_textRenderPass", _textRenderPass);

	shared_ptr<RenderPass> _textureRenderPass = make_shared<RenderPass>();
	_textureRenderPass->SetShader(_textureShader);
	_textureRenderPass->SetCamera(_mainCameraComponent);
	AddRenderPass("_textureRenderPass", _textureRenderPass);

	shared_ptr<RenderPass> _enemyRenderPass = make_shared<RenderPass>();
	_enemyRenderPass->SetShader(_enemyShader);
	_enemyRenderPass->SetCamera(_mainCameraComponent);
	_enemyRenderPass->SetUniformSet(_enemyUniforms);
	AddRenderPass("_enemyRenderPass", _enemyRenderPass);

	shared_ptr<RenderPass> _playerRenderPass = make_shared<RenderPass>();
	_playerRenderPass->SetShader(_playerShader);
	_playerRenderPass->SetCamera(_mainCameraComponent);
	_playerRenderPass->SetUniformSet(_playerUniforms);
	AddRenderPass("_playerRenderPass", _playerRenderPass);

	shared_ptr<RenderPass> _bulletRenderPass = make_shared<RenderPass>();
	_bulletRenderPass->SetShader(_bulletShader);
	_bulletRenderPass->SetCamera(_mainCameraComponent);
	_bulletRenderPass->SetUniformSet(_bulletUniforms);
	AddRenderPass("_bulletRenderPass", _bulletRenderPass);

	shared_ptr<RenderPass> _uiRenderPass = make_shared<RenderPass>();
	_uiRenderPass->SetShader(_uiShader);
	_uiRenderPass->SetCamera(_uiCameraComponent);
	AddRenderPass("_uiRenderPass", _uiRenderPass);

	/* FOR DEBUG */
	shared_ptr<RenderPass> _debugRenderPass = make_shared<RenderPass>();
	_debugRenderPass->SetShader(_debugShader);
	_debugRenderPass->SetCamera(_mainCameraComponent);
	AddRenderPass("_debugRenderPass", _debugRenderPass);
}

void InGame::LoadResources()
{
	/*================
	//    Audios    //
	================*/
	shared_ptr<BGM> MyBGM = make_shared<BGM>("PowerUp", "../Resources/Audio/BGM/power_up.mp3", FMOD_LOOP_NORMAL);
	AUDIO.AddBGM(MyBGM);

	/*=====================
	//    Backgrounds    //
	=====================*/
	shared_ptr<Texture> _groundTexture = make_shared<Texture>("Ground", "../Resources/Images/Extras/groundBig.png");
	_groundTexture->Init();
	RESOURCE.AddResource(_groundTexture);

	shared_ptr<Texture> _backgroundTexture1 = make_shared<Texture>("Background1", "../Resources/Images/Extras/background2.png");
	_backgroundTexture1->Init();
	RESOURCE.AddResource(_backgroundTexture1);

	shared_ptr<Texture> _backgroundTexture2 = make_shared<Texture>("Background2", "../Resources/Images/Extras/background1.png");
	_backgroundTexture2->Init();
	RESOURCE.AddResource(_backgroundTexture2);

	shared_ptr<Texture> _sideWallTexture = make_shared<Texture>("SideWall", "../Resources/Images/Extras/sidewall.png");
	_sideWallTexture->Init();
	RESOURCE.AddResource(_sideWallTexture);

	shared_ptr<Texture> _houseTexture2 = make_shared<Texture>("House2", "../Resources/Images/Extras/house2.png");
	_houseTexture2->Init();
	RESOURCE.AddResource(_houseTexture2);

	shared_ptr<Texture>_houseTexture3 = make_shared<Texture>("House3", "../Resources/Images/Extras/house3.png");
	_houseTexture3->Init();
	RESOURCE.AddResource(_houseTexture3);

	shared_ptr<Texture> _buildingTexture1 = make_shared<Texture>("Building1", "../Resources/Images/Extras/building1.png");
	_buildingTexture1->Init();
	RESOURCE.AddResource(_buildingTexture1);

	shared_ptr<Texture> _buildingTexture2 = make_shared<Texture>("Building2", "../Resources/Images/Extras/building2.png");
	_buildingTexture2->Init();
	RESOURCE.AddResource(_buildingTexture2);

	shared_ptr<Texture> _buildingTexture3 = make_shared<Texture>("Building3", "../Resources/Images/Extras/building3.png");
	_buildingTexture3->Init();
	RESOURCE.AddResource(_buildingTexture3);

	shared_ptr<Texture> _bushTexture = make_shared<Texture>("Bush", "../Resources/Images/Extras/grass_foreground.png");
	_bushTexture->Init();
	RESOURCE.AddResource(_bushTexture);

	shared_ptr<Texture>_treeTexture1 = make_shared<Texture>("Tree1", "../Resources/Images/Extras/tree1.png");
	_treeTexture1->Init();
	RESOURCE.AddResource(_treeTexture1);

	shared_ptr<Texture>_treeTexture2 = make_shared<Texture>("Tree2", "../Resources/Images/Extras/tree2.png");
	_treeTexture2->Init();
	RESOURCE.AddResource(_treeTexture2);

	/*==========================
	//    Player Flipbooks    //
	==========================*/
	#pragma region PLAYER_FLIPBOOK_NORMAL
		// Climb
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
			shared_ptr<Flipbook> _normal_climb = make_shared<Flipbook>("_normal_climb", "../Resources/Images/Flipbooks/Player_normal/FB_Player_climb.png", info);
			_normal_climb->Init();
			RESOURCE.AddResource(_normal_climb);
		}

		// Combo #1
		{
			FlipbookInfo info{ 1, 5, 0, 0, 4, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_combo_1_r = make_shared<Flipbook>("_normal_combo_1_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_1_right.png", info);
			_normal_combo_1_r->Init();
			RESOURCE.AddResource(_normal_combo_1_r);
		}

		// Combo #2
		{
			FlipbookInfo info{ 1, 9, 0, 0, 8, 30.0f, true, false };
			shared_ptr<Flipbook> _normal_combo_2_r = make_shared<Flipbook>("_normal_combo_2_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_2_right.png", info);
			_normal_combo_2_r->Init();
			RESOURCE.AddResource(_normal_combo_2_r);
		}

		// Combo #3
		{
			FlipbookInfo info{ 1, 5, 0, 0, 4, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_combo_3_r = make_shared<Flipbook>("_normal_combo_3_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_3_right.png", info);
			_normal_combo_3_r->Init();
			RESOURCE.AddResource(_normal_combo_3_r);
		}

		// Damaged
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_damaged_r = make_shared<Flipbook>("_normal_damaged_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_damaged_right.png", info);
			_normal_damaged_r->Init();
			RESOURCE.AddResource(_normal_damaged_r);
		}

		// Dash
		{
			FlipbookInfo info{ 1, 6, 0, 0, 5, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_dash_r = make_shared<Flipbook>("_normal_dash_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_dash_forward_right.png", info);
			_normal_dash_r->Init();
			RESOURCE.AddResource(_normal_dash_r);
		}

		// Died
		{
			FlipbookInfo info{ 1, 10, 0, 0, 9, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_died_r = make_shared<Flipbook>("_normal_died_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_died_right.png", info);
			_normal_died_r->Init();
			RESOURCE.AddResource(_normal_died_r);
		}

		// Fall
		{
			FlipbookInfo info{ 1, 2, 0, 0, 1, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_fall_r = make_shared<Flipbook>("_normal_fall_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_fall_right.png", info);
			_normal_fall_r->Init();
			RESOURCE.AddResource(_normal_fall_r);
		}

		// Idle
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _normal_idle_r = make_shared<Flipbook>("_normal_idle_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_idle_right.png", info);
			_normal_idle_r->Init();
			RESOURCE.AddResource(_normal_idle_r);
		}

		// Jump
		{
			FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, false };
			shared_ptr<Flipbook> _normal_jump_r = make_shared<Flipbook>("_normal_jump_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_jump_right.png", info);
			_normal_jump_r->Init();
			RESOURCE.AddResource(_normal_jump_r);
		}

		// Run
		{
			FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
			shared_ptr<Flipbook> _normal_run_r = make_shared<Flipbook>("_normal_run_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_run_right.png", info);
			_normal_run_r->Init();
			RESOURCE.AddResource(_normal_run_r);
		}

		// Slide
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_slide_r = make_shared<Flipbook>("_normal_slide_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_slide_right.png", info);
			_normal_slide_r->Init();
			RESOURCE.AddResource(_normal_slide_r);
		}

		// Walk
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _normal_walk_r = make_shared<Flipbook>("_normal_walk_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_walk_right.png", info);
			_normal_walk_r->Init();
			RESOURCE.AddResource(_normal_walk_r);
		}

		// Wallslide
		{
			FlipbookInfo info{ 1, 2, 0, 0, 1, 20.0f, true, false };
			shared_ptr<Flipbook> _normal_wallslide_r = make_shared<Flipbook>("_normal_wallslide_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_wallslide_right.png", info);
			_normal_wallslide_r->Init();
			RESOURCE.AddResource(_normal_wallslide_r);
		}
	#pragma endregion

	#pragma region PLAYER_FLIPBOOK_GUN
		// Climb
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_climb = make_shared<Flipbook>("_gun_climb", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_climb.png", info);
			_gun_climb->Init();
			RESOURCE.AddResource(_gun_climb);
		}

		// Air Attack
		{
			FlipbookInfo info{ 1, 2, 0, 0, 1, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_air_attack_r = make_shared<Flipbook>("_gun_air_attack_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_air_attack_right.png", info);
			_gun_air_attack_r->Init();
			RESOURCE.AddResource(_gun_air_attack_r);
		}

		// Damage
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_damaged_r = make_shared<Flipbook>("_gun_damaged_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_damaged_right.png", info);
			_gun_damaged_r->Init();
			RESOURCE.AddResource(_gun_damaged_r);
		}

		// Dash
		{
			FlipbookInfo info{ 1, 6, 0, 0, 5, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_dash_r = make_shared<Flipbook>("_gun_dash_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_dash_right.png", info);
			_gun_dash_r->Init();
			RESOURCE.AddResource(_gun_dash_r);
		}

		// Died
		{
			FlipbookInfo info{ 1, 10, 0, 0, 9, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_died_r = make_shared<Flipbook>("_gun_died_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_died_right.png", info);
			_gun_died_r->Init();
			RESOURCE.AddResource(_gun_died_r);
		}

		// Idle
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _gun_idle_r = make_shared<Flipbook>("_gun_idle_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_idle_right.png", info);
			_gun_idle_r->Init();
			RESOURCE.AddResource(_gun_idle_r);
		}

		// Jump
		{
			FlipbookInfo info{ 1, 5, 0, 0, 4, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_jump_r = make_shared<Flipbook>("_gun_jump_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_jump_right.png", info);
			_gun_jump_r->Init();
			RESOURCE.AddResource(_gun_jump_r);
		}

		// Run
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _gun_run_r = make_shared<Flipbook>("_gun_run_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_run_right.png", info);
			_gun_run_r->Init();
			RESOURCE.AddResource(_gun_run_r);
		}

		// Shot
		{
			FlipbookInfo info{ 1, 2, 0, 0, 1, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_shot_r = make_shared<Flipbook>("_gun_shot_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_shot_right.png", info);
			_gun_shot_r->Init();
			RESOURCE.AddResource(_gun_shot_r);
		}

		// Slide
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_slide_r = make_shared<Flipbook>("_gun_slide_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_slide_right.png", info);
			_gun_slide_r->Init();
			RESOURCE.AddResource(_gun_slide_r);
		}

		// Walk
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _gun_walk_r = make_shared<Flipbook>("_gun_walk_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_walk_right.png", info);
			_gun_walk_r->Init();
			RESOURCE.AddResource(_gun_walk_r);
		}

		// Wallslide
		{
			FlipbookInfo info{ 1, 2, 0, 0, 1, 20.0f, true, false };
			shared_ptr<Flipbook> _gun_wallslide_r = make_shared<Flipbook>("_gun_wallslide_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_wallslide_right.png", info);
			_gun_wallslide_r->Init();
			RESOURCE.AddResource(_gun_wallslide_r);
		}
	#pragma endregion

	#pragma region PLAYER_FLIPBOOK_SWORD
		// Climb
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_climb = make_shared<Flipbook>("_sword_climb", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_climb.png", info);
			_sword_climb->Init();
			RESOURCE.AddResource(_sword_climb);
		}

		// Air Attack
		{
			FlipbookInfo info{ 1, 2, 0, 0, 1, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_air_attack_r = make_shared<Flipbook>("_sword_air_attack_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_air_attack_right.png", info);
			_sword_air_attack_r->Init();
			RESOURCE.AddResource(_sword_air_attack_r);
		}

		// Combo #1
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_combo_1_r = make_shared<Flipbook>("_sword_combo_1_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_combo_1_right.png", info);
			_sword_combo_1_r->Init();
			RESOURCE.AddResource(_sword_combo_1_r);
		}

		// Combo #2
		{
			FlipbookInfo info{ 1, 3, 0, 0, 2, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_combo_2_r = make_shared<Flipbook>("_sword_combo_2_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_combo_2_right.png", info);
			_sword_combo_2_r->Init();
			RESOURCE.AddResource(_sword_combo_2_r);
		}

		// Combo #3
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_combo_3_r = make_shared<Flipbook>("_sword_combo_3_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_combo_3_right.png", info);
			_sword_combo_3_r->Init();
			RESOURCE.AddResource(_sword_combo_3_r);
		}

		// Damage
		{
			FlipbookInfo info{ 1, 4, 0, 0, 3, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_damaged_r = make_shared<Flipbook>("_sword_damaged_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_damaged_right.png", info);
			_sword_damaged_r->Init();
			RESOURCE.AddResource(_sword_damaged_r);
		}

		// Dash
		{
			FlipbookInfo info{ 1, 6, 0, 0, 5, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_dash_r = make_shared<Flipbook>("_sword_dash_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_dash_right.png", info);
			_sword_dash_r->Init();
			RESOURCE.AddResource(_sword_dash_r);
		}

		// Died
		{
			FlipbookInfo info{ 1, 10, 0, 0, 9, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_died_r = make_shared<Flipbook>("_sword_died_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_died_right.png", info);
			_sword_died_r->Init();
			RESOURCE.AddResource(_sword_died_r);
		}

		// Idle
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _sword_idle_r = make_shared<Flipbook>("_sword_idle_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_idle_right.png", info);
			_sword_idle_r->Init();
			RESOURCE.AddResource(_sword_idle_r);
		}

		// Jump
		{
			FlipbookInfo info{ 1, 5, 0, 0, 4, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_jump_r = make_shared<Flipbook>("_sword_jump_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_jump_right.png", info);
			_sword_jump_r->Init();
			RESOURCE.AddResource(_sword_jump_r);
		}

		// Run
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _sword_run_r = make_shared<Flipbook>("_sword_run_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_run_right.png", info);
			_sword_run_r->Init();
			RESOURCE.AddResource(_sword_run_r);
		}

		// Slide
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_slide_r = make_shared<Flipbook>("_sword_slide_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_slide_right.png", info);
			_sword_slide_r->Init();
			RESOURCE.AddResource(_sword_slide_r);
		}

		// Walk
		{
			FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
			shared_ptr<Flipbook> _sword_walk_r = make_shared<Flipbook>("_sword_walk_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_walk_right.png", info);
			_sword_walk_r->Init();
			RESOURCE.AddResource(_sword_walk_r);
		}

		// Wallslide
		{
			FlipbookInfo info{ 1, 2, 0, 0, 1, 20.0f, true, false };
			shared_ptr<Flipbook> _sword_wallslide_r = make_shared<Flipbook>("_sword_wallslide_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_wallslide_right.png", info);
			_sword_wallslide_r->Init();
			RESOURCE.AddResource(_sword_wallslide_r);
		}
	#pragma endregion

	/*===============
	//    Props    //
	===============*/
	shared_ptr<Texture> _bulletTexture = make_shared<Texture>("BulletTexture", "../Resources/Images/Extras/bullet.png");
	_bulletTexture->Init();
	RESOURCE.AddResource(_bulletTexture);

	/*===================
	//    FOR DEBUG    //
	===================*/
	shared_ptr<Texture> _debugTexture1 = make_shared<Texture>("TEST1", "../Resources/Images/debug_red.png");
	_debugTexture1->Init();
	RESOURCE.AddResource(_debugTexture1);

	shared_ptr<Texture> _debugTexture2 = make_shared<Texture>("TEST2", "../Resources/Images/debug_green.png");
	_debugTexture2->Init();
	RESOURCE.AddResource(_debugTexture2);

	shared_ptr<Texture> _debugTexture3 = make_shared<Texture>("TEST3", "../Resources/Images/debug_blue.png");
	_debugTexture3->Init();
	RESOURCE.AddResource(_debugTexture3);

	/*=========================
	//    Main InGame HUD    //
	=========================*/
	shared_ptr<Texture> _healthTexture = make_shared<Texture>("heart", "../Resources/Images/UIs/health.png");
	_healthTexture->Init();
	RESOURCE.AddResource(_healthTexture);

	shared_ptr<Font> _scoreText = make_shared<Font>("Score", "../Resources/Fonts/Gamer.ttf", "Score:", 96, Colors::White);
	_scoreText->Init();
	RESOURCE.AddResource(_scoreText);

	shared_ptr<Font> _normalText = make_shared<Font>("Normal", "../Resources/Fonts/Gamer.ttf", "Normal", 96, Colors::White);
	_normalText->Init();
	RESOURCE.AddResource(_normalText);

	shared_ptr<Font> _pistolText = make_shared<Font>("Pistol", "../Resources/Fonts/Gamer.ttf", "Pistol", 96, Colors::White);
	_pistolText->Init();
	RESOURCE.AddResource(_pistolText);

	shared_ptr<Font> _swordText = make_shared<Font>("Sword", "../Resources/Fonts/Gamer.ttf", "Sword", 96, Colors::White);
	_swordText->Init();
	RESOURCE.AddResource(_swordText);

	vector<shared_ptr<Font>> _numberText(10);
	for (int i = 0; i <= 9; i++)
	{
		string num = to_string(i);
		_numberText[i] = make_shared<Font>(num, "../Resources/Fonts/Gamer.ttf", num, 96, Colors::White);
		_numberText[i]->Init();
		RESOURCE.AddResource(_numberText[i]);
	}

	/*================
	//    Prefabs   //
	================*/
	auto self = shared_from_this();

	shared_ptr<Ground> ground = make_shared<Ground>("Ground");
	ground->SetCurrentScene(self);

	shared_ptr<Background1> background1 = make_shared<Background1>("Background1");
	background1->SetCurrentScene(self);

	shared_ptr<Background2> background2 = make_shared<Background2>("Background2");
	background2->SetCurrentScene(self);

	shared_ptr<SideWall> sideWall = make_shared<SideWall>("SideWall");
	sideWall->SetCurrentScene(self);

	shared_ptr<House2> house2 = make_shared<House2>("House2");
	house2->SetCurrentScene(self);

	shared_ptr<House3> house3 = make_shared<House3>("House3");
	house3->SetCurrentScene(self);

	shared_ptr<Building1> building1 = make_shared<Building1>("Building1");
	building1->SetCurrentScene(self);

	shared_ptr<Building2> building2 = make_shared<Building2>("Building2");
	building2->SetCurrentScene(self);

	shared_ptr<Building3> building3 = make_shared<Building3>("Building3");
	building3->SetCurrentScene(self);

	shared_ptr<Bush> bush = make_shared<Bush>("Bush");
	bush->SetCurrentScene(self);

	shared_ptr<Tree1> tree1 = make_shared<Tree1>("Tree1");
	tree1->SetCurrentScene(self);

	shared_ptr<Tree2> tree2 = make_shared<Tree2>("Tree2");
	tree2->SetCurrentScene(self);

	shared_ptr<UIPlayerHUD> mainHUD = make_shared<UIPlayerHUD>("MainHUD");
	mainHUD->SetCurrentScene(shared_from_this());

	shared_ptr<Bullet> bullet = make_shared<Bullet>("Bullet");
	bullet->SetCurrentScene(self);
	RESOURCE.AddResource(bullet);

	shared_ptr<Player> _player = make_shared<Player>("Player");
	_player->SetCurrentScene(self);

	shared_ptr<Enemy> _enemy = make_shared<Enemy>("Enemy");
	_enemy->SetCurrentScene(self);

	/* FOR DEBUG */
	shared_ptr<ColliderDebuger> debugPrf = make_shared<ColliderDebuger>("DebugPrefab");
	debugPrf->SetCurrentScene(self);
}

void InGame::CreateSceneContext()
{
	// Set clear color
	RENDER.SetClearColor({ 0.61f, 0.81f, 0.83f, 1.0f });

	// Set render properties
	CreateRenderProperties();

	// Load nessesary resources
	LoadResources();

#pragma region SCENE_CONTEXT

	/*==============================
	//		MAIN_SCENE_CONTEXT    //
	==============================*/
	auto self = shared_from_this();

	// Background
	shared_ptr<Background1> _background1 = make_shared<Background1>("Background1");
	_background1->SetCurrentScene(self);
	auto background1_1 = _background1->Instantiate("Background1_1", { 0.0f, -150.0f, 0.f });
	_gameObjects.push_back(background1_1);
	auto background1_2 = _background1->Instantiate("Background1_2", { 1100.0f, -150.0f, 0.f });
	_gameObjects.push_back(background1_2);
	auto background1_3 = _background1->Instantiate("Background1_3", { 2200.0f, -150.0f, 0.f });
	_gameObjects.push_back(background1_3);
	auto background1_4 = _background1->Instantiate("Background1_4", { 3300.0f, -150.0f, 0.f });
	_gameObjects.push_back(background1_4);

	shared_ptr<Background2> _background2 = make_shared<Background2>("Background2");
	_background2->SetCurrentScene(self);
	auto background2_1 = _background2->Instantiate("Background2_1", { 0.0f, -200.0f, 0.f });
	_gameObjects.push_back(background2_1);
	auto background2_2 = _background2->Instantiate("Background2_2", { 1100.0f, -200.0f, 0.f });
	_gameObjects.push_back(background2_2);
	auto background2_3 = _background2->Instantiate("Background2_3", { 2200.0f, -200.0f, 0.f });
	_gameObjects.push_back(background2_3);
	auto background2_4 = _background2->Instantiate("Background2_4", { 3300.0f, -200.0f, 0.f });
	_gameObjects.push_back(background2_4);

	shared_ptr<Bush> _bush = make_shared<Bush>("Bush");
	_bush->SetCurrentScene(self);
	auto bush_1 = _bush->Instantiate("Bush_1", { -700.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush_1);
	auto bush_2 = _bush->Instantiate("Bush_2", { 0.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush_2);
	auto bush_3 = _bush->Instantiate("Bush_3", { 680.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush_3);
	auto bush_4 = _bush->Instantiate("Bush_4", { 1360.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush_4);
	auto bush_5 = _bush->Instantiate("Bush_5", { 2040.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush_5);
	auto bush_6 = _bush->Instantiate("Bush_6", { 2720.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush_6);

	shared_ptr<Tree1> _tree1 = make_shared<Tree1>("Tree1");
	_tree1->SetCurrentScene(self);
	shared_ptr<Tree2> _tree2 = make_shared<Tree2>("Tree2");
	_tree2->SetCurrentScene(self);
	auto tree_1 = _tree1->Instantiate("Tree1", { -200.0f, 0.0f, 0.0f });
	_gameObjects.push_back(tree_1);
	auto tree_2 = _tree2->Instantiate("Tree2", { 500.0f, 100.0f, 0.0f });
	_gameObjects.push_back(tree_2);
	auto tree_3 = _tree1->Instantiate("Tree3", { 1400.0f, 0.0f, 0.0f });
	_gameObjects.push_back(tree_3);
	auto tree_4 = _tree2->Instantiate("Tree4", { 2000.0f, 100.0f, 0.0f });
	_gameObjects.push_back(tree_4);

	shared_ptr<Ground> _ground = make_shared<Ground>("Ground");
	_ground->SetCurrentScene(self);
	auto ground_1 = _ground->Instantiate("Ground1", { -700.0f, -320.0f, 0.f });
	_gameObjects.push_back(ground_1);
	auto ground_2 = _ground->Instantiate("Ground2", { 0.0f, -320.0f, 0.f });
	_gameObjects.push_back(ground_2);
	auto ground_3 = _ground->Instantiate("Ground3", { 760.0f, -320.0f, 0.f });
	_gameObjects.push_back(ground_3);
	auto ground_4 = _ground->Instantiate("Ground4", { 1520, -320.0f, 0.f });
	_gameObjects.push_back(ground_4);
	auto ground_5 = _ground->Instantiate("Ground5", { 2200.0f, -320.0f, 0.f });
	_gameObjects.push_back(ground_5);
	auto ground_6 = _ground->Instantiate("Ground6", { 2700.0f, -320.0f, 0.f });
	_gameObjects.push_back(ground_6);

	shared_ptr<Building2> _building2 = make_shared<Building2>("Building2");
	_building2->SetCurrentScene(self);
	auto building2 = _building2->Instantiate("Building2", { 100.0f, 45.0f, 0.0f });
	_gameObjects.push_back(building2);

	shared_ptr<House2> _house2 = make_shared<House2>("House2");
	_house2->SetCurrentScene(self);
	auto house2 = _house2->Instantiate("House2", { -300.0f, -35.0f, 0.0f });
	_gameObjects.push_back(house2);

	shared_ptr<Building1> _buildling1 = make_shared<Building1>("Building1");
	_buildling1->SetCurrentScene(self);
	auto building1 = _buildling1->Instantiate("Building1", { 1000.0f, 80.0f, 0.0f });
	_gameObjects.push_back(building1);

	shared_ptr<Building3> _building3 = make_shared<Building3>("Building3");
	_building3->SetCurrentScene(self);
	auto building3 = _building3->Instantiate("Building3", { 1700.0f, 30.0f, 0.0f });
	_gameObjects.push_back(building3);

	shared_ptr<House3> _house3 = make_shared<House3>("House3");
	_house3->SetCurrentScene(self);
	auto house3 = _house3->Instantiate("House3", { 2500.0f, 20.0f, 0.0f });
	_gameObjects.push_back(house3);

	shared_ptr<SideWall> _sideWall = make_shared<SideWall>("SideWall");
	_sideWall->SetCurrentScene(self);
	auto sideWall = _sideWall->Instantiate("SideWall", { -550.0f, 200.0f, 0.0f }, glm::vec3(0.0f), glm::vec3(0.5f, 0.65f, 0.5f));
	_gameObjects.push_back(sideWall);

	// Main Characters
	shared_ptr<Player> _player = make_shared<Player>("Player");
	_player->SetCurrentScene(self);
	auto player = _player->Instantiate("Player", { -300.0f, -140.0f, 0.0f });
	_gameObjects.push_back(player);

	shared_ptr<Enemy> _enemy = make_shared<Enemy>("Enemy");
	_enemy->SetCurrentScene(self);
	auto enemy = _enemy->Instantiate("Enemy", { 400, -140.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.1f, 1.1f, 0.0f });
	_gameObjects.push_back(enemy);

	// Main HUD UI
	shared_ptr<UIPlayerHUD> _mainHUD = make_shared<UIPlayerHUD>("mainHUD");
	_mainHUD->SetCurrentScene(self);
	auto hud = _mainHUD->Instantiate("mainHUD", { 0.0f, 0.0f, 0.0f });
	_gameObjects.push_back(hud);


	// Add RenderPasses to RenderManager
	RENDER.AddRenderPass(GetRenderPass("_textureRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_playerRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_enemyRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_bulletRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_textRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_uiRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_debugRenderPass"));

	// Play BGM
	AUDIO.PlayBGM("PowerUp");
}

