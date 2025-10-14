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
#include "UIPlayerHUD.h"
#pragma endregion

#pragma region Scripts
#include "CameraController.h"
#pragma endregion

InGame::InGame(const string& name) : Super(name)
{

}

void InGame::LoadResources()
{
	shared_ptr<BGM> MyBGM = make_shared<BGM>
	(
		"PowerUp",
		"../Resources/Audio/BGM/power_up.mp3",
		FMOD_LOOP_NORMAL
	);
	RESOURCE.AddResource(MyBGM);
	AUDIO.AddBGM(MyBGM);

	// Load Resources
	{
		// Background
		{
			_groundTexture = make_shared<Texture>("Ground", "../Resources/Images/Extras/groundBig.png");
			_groundTexture->Init();
			RESOURCE.AddResource(_groundTexture);

			_backgroundTexture1 = make_shared<Texture>("Background1", "../Resources/Images/Extras/background2.png");
			_backgroundTexture1->Init();
			RESOURCE.AddResource(_backgroundTexture1);

			_backgroundTexture2 = make_shared<Texture>("Background2", "../Resources/Images/Extras/background1.png");
			_backgroundTexture2->Init();
			RESOURCE.AddResource(_backgroundTexture2);

			_sideWallTexture = make_shared<Texture>("SideWall", "../Resources/Images/Extras/sidewall.png");
			_sideWallTexture->Init();
			RESOURCE.AddResource(_sideWallTexture);

			_houseTexture2 = make_shared<Texture>("House2", "../Resources/Images/Extras/house2.png");
			_houseTexture2->Init();
			RESOURCE.AddResource(_houseTexture2);

			_houseTexture3 = make_shared<Texture>("House3", "../Resources/Images/Extras/house3.png");
			_houseTexture3->Init();
			RESOURCE.AddResource(_houseTexture3);

			_buildingTexture1 = make_shared<Texture>("Building1", "../Resources/Images/Extras/building1.png");
			_buildingTexture1->Init();
			RESOURCE.AddResource(_buildingTexture1);

			_buildingTexture2 = make_shared<Texture>("Building2", "../Resources/Images/Extras/building2.png");
			_buildingTexture2->Init();
			RESOURCE.AddResource(_buildingTexture2);

			_buildingTexture3 = make_shared<Texture>("Building3", "../Resources/Images/Extras/building3.png");
			_buildingTexture3->Init();
			RESOURCE.AddResource(_buildingTexture3);

			_bushTexture = make_shared<Texture>("Bush", "../Resources/Images/Extras/grass_foreground.png");
			_bushTexture->Init();
			RESOURCE.AddResource(_bushTexture);

			_treeTexture1 = make_shared<Texture>("Tree1", "../Resources/Images/Extras/tree1.png");
			_treeTexture1->Init();
			RESOURCE.AddResource(_treeTexture1);

			_treeTexture2 = make_shared<Texture>("Tree2", "../Resources/Images/Extras/tree2.png");
			_treeTexture2->Init();
			RESOURCE.AddResource(_treeTexture2);
		}

		// Load Player flipbooks
		{
			#pragma region PLAYER_FLIPBOOK_NORMAL
			// Climb
			{
				FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
				_normal_climb = make_shared<Flipbook>("_normal_climb", "../Resources/Images/Flipbooks/Player_normal/FB_Player_climb.png", info);
				_normal_climb->Init();
				RESOURCE.AddResource(_normal_climb);
			}

			// Combo #1
			{
				FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
				_normal_combo_1_r = make_shared<Flipbook>("_normal_combo_1_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_1_right.png", info);
				_normal_combo_1_r->Init();
				RESOURCE.AddResource(_normal_combo_1_r);
			}

			// Combo #2
			{
				FlipbookInfo info{ 1, 9, 0, 0, 8, 16.0f, true, true };
				_normal_combo_2_r = make_shared<Flipbook>("_normal_combo_2_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_2_right.png", info);
				_normal_combo_2_r->Init();
				RESOURCE.AddResource(_normal_combo_2_r);
			}

			// Combo #3
			{
				FlipbookInfo info{ 1, 9, 0, 0, 8, 16.0f, true, true };
				_normal_combo_3_r = make_shared<Flipbook>("_normal_combo_3_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_3_right.png", info);
				_normal_combo_3_r->Init();
				RESOURCE.AddResource(_normal_combo_3_r);
			}

			// Damaged
			{
				FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
				_normal_damaged_r = make_shared<Flipbook>("_normal_damaged_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_damaged_right.png", info);
				_normal_damaged_r->Init();
				RESOURCE.AddResource(_normal_damaged_r);
			}

			// Dash
			{
				FlipbookInfo info{ 1, 6, 0, 0, 5, 16.0f, true, true };
				_normal_dash_r = make_shared<Flipbook>("_normal_dash_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_dash_forward_right.png", info);
				_normal_dash_r->Init();
				RESOURCE.AddResource(_normal_dash_r);
			}

			// Died
			{
				FlipbookInfo info{ 1, 10, 0, 0, 9, 16.0f, true, true };
				_normal_died_r = make_shared<Flipbook>("_normal_died_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_died_right.png", info);
				_normal_died_r->Init();
				RESOURCE.AddResource(_normal_died_r);
			}

			// Fall
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_normal_fall_r = make_shared<Flipbook>("_normal_fall_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_fall_right.png", info);
				_normal_fall_r->Init();
				RESOURCE.AddResource(_normal_fall_r);
			}

			// Idle
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_normal_idle_r = make_shared<Flipbook>("_normal_idle_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_idle_right.png", info);
				_normal_idle_r->Init();
				RESOURCE.AddResource(_normal_idle_r);
			}

			// Jump
			{
				FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
				_normal_jump_r = make_shared<Flipbook>("_normal_jump_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_jump_right.png", info);
				_normal_jump_r->Init();
				RESOURCE.AddResource(_normal_jump_r);
			}

			// Run
			{
				FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
				_normal_run_r = make_shared<Flipbook>("_normal_run_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_run_right.png", info);
				_normal_run_r->Init();
				RESOURCE.AddResource(_normal_run_r);
			}

			// Slide
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_normal_slide_r = make_shared<Flipbook>("_normal_slide_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_slide_right.png", info);
				_normal_slide_r->Init();
				RESOURCE.AddResource(_normal_slide_r);
			}

			// Walk
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_normal_walk_r = make_shared<Flipbook>("_normal_walk_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_walk_right.png", info);
				_normal_walk_r->Init();
				RESOURCE.AddResource(_normal_walk_r);
			}

			// Wallslide
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_normal_wallslide_r = make_shared<Flipbook>("_normal_wallslide_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_wallslide_right.png", info);
				_normal_wallslide_r->Init();
				RESOURCE.AddResource(_normal_wallslide_r);
			}
			#pragma endregion
			
			#pragma region PLAYER_FLIPBOOK_GUN
			// Climb
			{
				FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
				_gun_climb = make_shared<Flipbook>("_gun_climb", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_climb.png", info);
				_gun_climb->Init();
				RESOURCE.AddResource(_gun_climb);
			}

			// Air Attack
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_gun_air_attack_r = make_shared<Flipbook>("_gun_air_attack_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_air_attack_right.png", info);
				_gun_air_attack_r->Init();
				RESOURCE.AddResource(_gun_air_attack_r);
			}

			// Damage
			{
				FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
				_gun_damaged_r = make_shared<Flipbook>("_gun_damaged_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_damaged_right.png", info);
				_gun_damaged_r->Init();
				RESOURCE.AddResource(_gun_damaged_r);
			}

			// Dash
			{
				FlipbookInfo info{ 1, 6, 0, 0, 5, 16.0f, true, true };
				_gun_dash_r = make_shared<Flipbook>("_gun_dash_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_dash_right.png", info);
				_gun_dash_r->Init();
				RESOURCE.AddResource(_gun_dash_r);
			}

			// Died
			{
				FlipbookInfo info{ 1, 10, 0, 0, 9, 16.0f, true, true };
				_gun_died_r = make_shared<Flipbook>("_gun_died_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_died_right.png", info);
				_gun_died_r->Init();
				RESOURCE.AddResource(_gun_died_r);
			}

			// Idle
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_idle_r = make_shared<Flipbook>("_gun_idle_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_idle_right.png", info);
				_gun_idle_r->Init();
				RESOURCE.AddResource(_gun_idle_r);
			}

			// Jump
			{
				FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
				_gun_jump_r = make_shared<Flipbook>("_gun_jump_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_jump_right.png", info);
				_gun_jump_r->Init();
				RESOURCE.AddResource(_gun_jump_r);
			}

			// Run
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_run_r = make_shared<Flipbook>("_gun_run_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_run_right.png", info);
				_gun_run_r->Init();
				RESOURCE.AddResource(_gun_run_r);
			}

			// Shot
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_gun_shot_r = make_shared<Flipbook>("_gun_shot_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_shot_right.png", info);
				_gun_shot_r->Init();
				RESOURCE.AddResource(_gun_shot_r);
			}

			// Slide
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_slide_r = make_shared<Flipbook>("_gun_slide_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_slide_right.png", info);
				_gun_slide_r->Init();
				RESOURCE.AddResource(_gun_slide_r);
			}

			// Walk
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_walk_r = make_shared<Flipbook>("_gun_walk_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_walk_right.png", info);
				_gun_walk_r->Init();
				RESOURCE.AddResource(_gun_walk_r);
			}

			// Wallslide
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_gun_wallslide_r = make_shared<Flipbook>("_gun_wallslide_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_wallslide_right.png", info);
				_gun_wallslide_r->Init();
				RESOURCE.AddResource(_gun_wallslide_r);
			}
			#pragma endregion
		
			#pragma region PLAYER_FLIPBOOK_SWORD

			// Climb
			{
				FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
				_sword_climb = make_shared<Flipbook>("_sword_climb", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_climb.png", info);
				_sword_climb->Init();
				RESOURCE.AddResource(_sword_climb);
			}

			// Air Attack
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_sword_air_attack_r = make_shared<Flipbook>("_sword_air_attack_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_air_attack_right.png", info);
				_sword_air_attack_r->Init();
				RESOURCE.AddResource(_sword_air_attack_r);
			}

// Combo #1
{
	FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
	_sword_combo_1_r = make_shared<Flipbook>("_sword_combo_1_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_combo_1_right.png", info);
	_sword_combo_1_r->Init();
	RESOURCE.AddResource(_sword_combo_1_r);
			}

// Combo #2
{
	FlipbookInfo info{ 1, 3, 0, 0, 2, 16.0f, true, true };
	_sword_combo_2_r = make_shared<Flipbook>("_sword_combo_2_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_combo_2_right.png", info);
	_sword_combo_2_r->Init();
	RESOURCE.AddResource(_sword_combo_2_r);
}

// Combo #3
{
	FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
	_sword_combo_3_r = make_shared<Flipbook>("_sword_combo_3_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_combo_3_right.png", info);
	_sword_combo_3_r->Init();
	RESOURCE.AddResource(_sword_combo_3_r);
}

// Damage
{
	FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
	_sword_damaged_r = make_shared<Flipbook>("_sword_damaged_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_damaged_right.png", info);
	_sword_damaged_r->Init();
	RESOURCE.AddResource(_sword_damaged_r);
}

// Dash
{
	FlipbookInfo info{ 1, 6, 0, 0, 5, 16.0f, true, true };
	_sword_dash_r = make_shared<Flipbook>("_sword_dash_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_dash_right.png", info);
	_sword_dash_r->Init();
	RESOURCE.AddResource(_sword_dash_r);
}

// Died
{
	FlipbookInfo info{ 1, 10, 0, 0, 9, 16.0f, true, true };
	_sword_died_r = make_shared<Flipbook>("_sword_died_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_died_right.png", info);
	_sword_died_r->Init();
	RESOURCE.AddResource(_sword_died_r);
}

// Idle
{
	FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
	_sword_idle_r = make_shared<Flipbook>("_sword_died_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_idle_right.png", info);
	_sword_idle_r->Init();
	RESOURCE.AddResource(_sword_idle_r);
}

// Jump
{
	FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
	_sword_jump_r = make_shared<Flipbook>("_sword_jump_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_jump_right.png", info);
	_sword_jump_r->Init();
	RESOURCE.AddResource(_sword_jump_r);
}

// Run
{
	FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
	_sword_run_r = make_shared<Flipbook>("_sword_run_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_run_right.png", info);
	_sword_run_r->Init();
	RESOURCE.AddResource(_sword_run_r);
}

// Slide
{
	FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
	_sword_slide_r = make_shared<Flipbook>("_sword_slide_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_slide_right.png", info);
	_sword_slide_r->Init();
	RESOURCE.AddResource(_sword_slide_r);
}

// Walk
{
	FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
	_sword_walk_r = make_shared<Flipbook>("_sword_walk_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_walk_right.png", info);
	_sword_walk_r->Init();
	RESOURCE.AddResource(_sword_walk_r);
}

// Wallslide
{
	FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
	_sword_wallslide_r = make_shared<Flipbook>("_sword_wallslide_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_wallslide_right.png", info);
	_sword_wallslide_r->Init();
	RESOURCE.AddResource(_sword_wallslide_r);
}
#pragma endregion
		}

		// Main HUD UIs
		{
			_healthTexture = make_shared<Texture>("heart", "../Resources/Images/UIs/health.png");
			_healthTexture->Init();
			RESOURCE.AddResource(_healthTexture);

			_scoreText = make_shared<Font>("Score", "../Resources/Fonts/Gamer.ttf", "Score :", 96, Colors::White);
			_scoreText->Init();
			RESOURCE.AddResource(_scoreText);

			_noWeaponText = make_shared<Font>("NoWeapon", "../Resources/Fonts/Gamer.ttf", "No Weapon", 96, Colors::White);
			_noWeaponText->Init();
			RESOURCE.AddResource(_noWeaponText);

			for (int i = 0; i <= 9; i++)
			{
				string num = to_string(i);
				_numberText[i] = make_shared<Font>(num, "../Resources/Fonts/Gamer.ttf", num, 96, Colors::White);
				_numberText[i]->Init();
				RESOURCE.AddResource(_numberText[i]);
			}

			_numberText[10] = make_shared<Font>("slash", "../Resources/Fonts/Gamer.ttf", "/", 96, Colors::White);
			_numberText[10]->Init();
			RESOURCE.AddResource(_numberText[10]);

			_scoreText = make_shared<Font>("Score", "../Resources/Fonts/Gamer.ttf", "Score :", 96, Colors::White);
			_scoreText->Init();
			RESOURCE.AddResource(_scoreText);
		}
	}

	// Load Background Prefabs
	{
		_ground = make_shared<Ground>();
		_ground->SetRenderPass(_textureRenderPass);

		_background1 = make_shared<Background1>();
		_background1->SetRenderPass(_textureRenderPass);

		_background2 = make_shared<Background2>();
		_background2->SetRenderPass(_textureRenderPass);

		_sideWall = make_shared<SideWall>();
		_sideWall->SetRenderPass(_textureRenderPass);

		_house2 = make_shared<House2>();
		_house2->SetRenderPass(_textureRenderPass);

		_house3 = make_shared<House3>();
		_house3->SetRenderPass(_textureRenderPass);

		_building1 = make_shared<Building1>();
		_building1->SetRenderPass(_textureRenderPass);

		_building2 = make_shared<Building2>();
		_building2->SetRenderPass(_textureRenderPass);

		_building3 = make_shared<Building3>();
		_building3->SetRenderPass(_textureRenderPass);

		_bush = make_shared<Bush>();
		_bush->SetRenderPass(_textureRenderPass);

		_tree1 = make_shared<Tree1>();
		_tree1->SetRenderPass(_textureRenderPass);

		_tree2 = make_shared<Tree2>();
		_tree2->SetRenderPass(_textureRenderPass);
	}

	// Load GameObject prefabs
	{
		_player = make_shared<Player>();
		_player->SetRenderPass(_playerRenderpass);

		_mainHUD = make_shared<UIPlayerHUD>();
		_mainHUD->SetCurrentScene(shared_from_this());
		_mainHUD->SetRenderPass(_textRenderPass);
	}
}

void InGame::CreateRenderProperties()
{
	// Load default texture shaders
	{
		_textureShader = make_shared<Shader>("TextureShader", "../Resources/Shaders/default.vert", "../Resources/Shaders/default.frag");
		_textureShader->Init();
		_textureShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_textureShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_textureShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_textureShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		RESOURCE.AddResource(_textureShader);
	}

	// Load default text surface shaders
	{
		_textShader = make_shared<Shader>("TextShader", "../Resources/Shaders/text.vert", "../Resources/Shaders/text.frag");
		_textShader->Init();
		_textShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_textShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_textShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_textShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		_textShader->AddUniform(Uniforms::UNIFORM_COLOR);
		RESOURCE.AddResource(_textShader);
	}

	// Load hud shaders
	{
		_uiShader = make_shared<Shader>("TextShader", "../Resources/Shaders/hud.vert", "../Resources/Shaders/hud.frag");
		_uiShader->Init();
		_uiShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_uiShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_uiShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_uiShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		_uiShader->AddUniform(Uniforms::UNIFORM_COLOR);
		RESOURCE.AddResource(_uiShader);
	}

	// Load player shader
	{
		_playerShader = make_shared<Shader>("PlayerShader", "../Resources/Shaders/Character.vert", "../Resources/Shaders/Character.frag");
		_playerShader->Init();
		_playerShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_playerShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_playerShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_playerShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		_playerShader->AddUniform("flip");
		RESOURCE.AddResource(_playerShader);

		_playerUniforms = make_shared<UniformSet>("PlayerUniforms");
		_playerUniforms->Set("flip", false);
		RESOURCE.AddResource(_playerUniforms);
	}

	// Load Main camera
	{
		_mainCameraComponent = make_shared<Camera>("MainCameraComponent");
		_mainCamera = make_shared<GameObject>("MainCamera");
		_mainCamera->AddComponent(_mainCameraComponent);
		_mainCameraTransform = make_shared<Transform>
			(
				"MainCameraTransform",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_mainCamera->SetTransform(_mainCameraTransform);
		_mainCameraController = make_shared<CameraController>("CameraController");
		_mainCamera->AddBehaviour(_mainCameraController);
		_gameObjects.push_back(_mainCamera);
	}

	// Load UI camera
	{
		_uiCameraComponent = make_shared<Camera>("UICameraComponent");
		_uiCamera = make_shared<GameObject>("UICamera");
		_uiCamera->AddComponent(_uiCameraComponent);
		_uiCameraTransform = make_shared<Transform>
			(
				"UICameraTransform",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_uiCamera->SetTransform(_uiCameraTransform);
		_gameObjects.push_back(_uiCamera);
	}

	// Create render passes
	{
		_textRenderPass = make_shared<RenderPass>();
		_textRenderPass->SetShader(_textShader);
		_textRenderPass->SetCamera(_uiCameraComponent);

		_textureRenderPass = make_shared<RenderPass>();
		_textureRenderPass->SetShader(_textureShader);
		_textureRenderPass->SetCamera(_mainCameraComponent);

		_uiRenderPass = make_shared<RenderPass>();
		_uiRenderPass->SetShader(_uiShader);
		_uiRenderPass->SetCamera(_uiCameraComponent);
		
		_playerRenderpass = make_shared<RenderPass>();
		_playerRenderpass->SetShader(_playerShader);
		_playerRenderpass->SetCamera(_mainCameraComponent);
		_playerRenderpass->SetUniformSet(_playerUniforms);
	}
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

	// Prefabs
	{
		// Background
		{
			auto background1_1 = _background1->Instantiate("Background1_1", { 0.0f, -150.0f, 0.f });
			_gameObjects.push_back(background1_1);
			auto background1_2 = _background1->Instantiate("Background1_2", { 1100.0f, -150.0f, 0.f });
			_gameObjects.push_back(background1_2);
			auto background1_3 = _background1->Instantiate("Background1_3", { 2200.0f, -150.0f, 0.f });
			_gameObjects.push_back(background1_3);
			auto background1_4 = _background1->Instantiate("Background1_4", { 3300.0f, -150.0f, 0.f });
			_gameObjects.push_back(background1_4);

			auto background2_1 = _background2->Instantiate("Background2_1", { 0.0f, -200.0f, 0.f });
			_gameObjects.push_back(background2_1);
			auto background2_2 = _background2->Instantiate("Background2_2", { 1100.0f, -200.0f, 0.f });
			_gameObjects.push_back(background2_2);
			auto background2_3 = _background2->Instantiate("Background2_3", { 2200.0f, -200.0f, 0.f });
			_gameObjects.push_back(background2_3);
			auto background2_4 = _background2->Instantiate("Background2_4", { 3300.0f, -200.0f, 0.f });
			_gameObjects.push_back(background2_4);

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

			auto tree_1 = _tree1->Instantiate("Tree1", { -200.0f, 0.0f, 0.0f });
			_gameObjects.push_back(tree_1);
			auto tree_2 = _tree2->Instantiate("Tree2", { 500.0f, 100.0f, 0.0f });
			_gameObjects.push_back(tree_2);
			auto tree_3 = _tree1->Instantiate("Tree3", { 1400.0f, 0.0f, 0.0f });
			_gameObjects.push_back(tree_3);
			auto tree_4 = _tree2->Instantiate("Tree4", { 2000.0f, 100.0f, 0.0f });
			_gameObjects.push_back(tree_4);

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

			auto building2 = _building2->Instantiate("Building2", { 100.0f, 45.0f, 0.0f });
			_gameObjects.push_back(building2);
			auto house2 = _house2->Instantiate("House2", { -300.0f, -35.0f, 0.0f });
			_gameObjects.push_back(house2);
			auto building1 = _building1->Instantiate("Building1", { 1000.0f, 80.0f, 0.0f });
			_gameObjects.push_back(building1);
			auto building3 = _building3->Instantiate("Building3", { 1700.0f, 30.0f, 0.0f });
			_gameObjects.push_back(building3);
			auto house3 = _house3->Instantiate("House3", { 2500.0f, 20.0f, 0.0f });
			_gameObjects.push_back(house3);
		}

		// Buildings
		{
			auto sideWall = _sideWall->Instantiate("SideWall", { -550.0f, 200.0f, 0.0f }, glm::vec3(0.0f), glm::vec3(0.5f, 0.65f, 0.5f));
			_gameObjects.push_back(sideWall);
		}
	
		// GameObject
		{
			auto player = _player->Instantiate("Player", { -300.0f, -140.0f, 0.0f });
			_gameObjects.push_back(player);
		}

		// Main HUD
		{
			auto mainHUD = _mainHUD->Instantiate("MainHUD", { 0.0f, 0.0f ,0.0f });
			_gameObjects.push_back(mainHUD);

			_healthObject1 = make_shared<GameObject>("_healthObject1");
			_healthTransform1 = make_shared<Transform>
				(
					"_healthTransform1",
					glm::vec3(-550.0f, 350.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_healthObject1->SetTransform(_healthTransform1);
			_healthSprite1 = make_shared<Sprite>("_healthSprite1", RESOURCE.GetResource<Texture>("heart"));
			_healthObject1->AddRenderable(_healthSprite1);
			_uiRenderPass->AddRenderable(_healthSprite1);
			_gameObjects.push_back(_healthObject1);

			_healthObject2 = make_shared<GameObject>("_healthObject2");
			_healthTransform2 = make_shared<Transform>
				(
					"_healthTransform2",
					glm::vec3(-480.0f, 350.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_healthObject2->SetTransform(_healthTransform2);
			_healthSprite2 = make_shared<Sprite>("_healthSprite2", RESOURCE.GetResource<Texture>("heart"));
			_healthObject2->AddRenderable(_healthSprite2);
			_uiRenderPass->AddRenderable(_healthSprite2);
			_gameObjects.push_back(_healthObject2);

			_healthObject3 = make_shared<GameObject>("_healthObject3");
			_healthTransform3 = make_shared<Transform>
				(
					"_healthTransform3",
					glm::vec3(-410.0f, 350.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_healthObject3->SetTransform(_healthTransform3);
			_healthSprite3 = make_shared<Sprite>("_healthSprite3", RESOURCE.GetResource<Texture>("heart"));
			_healthObject3->AddRenderable(_healthSprite3);
			_uiRenderPass->AddRenderable(_healthSprite3);
			_gameObjects.push_back(_healthObject3);
		}
	}

#pragma region PRESENT_RENDER_PASSES
	RENDER.AddRenderPass(_textureRenderPass);
	RENDER.AddRenderPass(_playerRenderpass);
	RENDER.AddRenderPass(_uiRenderPass);
	RENDER.AddRenderPass(_textRenderPass);
#pragma endregion

#pragma region PLAY_BGM
	AUDIO.PlayBGM("PowerUp");
#pragma endregion

#pragma endregion
}

