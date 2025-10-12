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
#include "Bush.h"
#include "UISetting.h"
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

			_houseTexture1 = make_shared<Texture>("House1", "../Resources/Images/Extras/building2.png");
			_houseTexture1->Init();
			RESOURCE.AddResource(_houseTexture1);

			_houseTexture2 = make_shared<Texture>("House2", "../Resources/Images/Extras/house2.png");
			_houseTexture2->Init();
			RESOURCE.AddResource(_houseTexture2);

			_bushTexture = make_shared<Texture>("Bush", "../Resources/Images/Extras/grass_foreground.png");
			_bushTexture->Init();
			RESOURCE.AddResource(_bushTexture);
		}

		// Load Player flipbook : normal
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
				_normal_combo_1_l = make_shared<Flipbook>("_normal_combo_1_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_1_left.png", info);
				_normal_combo_1_l->Init();
				RESOURCE.AddResource(_normal_combo_1_l);

				_normal_combo_1_r = make_shared<Flipbook>("_normal_combo_1_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_1_right.png", info);
				_normal_combo_1_r->Init();
				RESOURCE.AddResource(_normal_combo_1_r);
			}

			// Combo #2
			{
				FlipbookInfo info{ 1, 9, 0, 0, 8, 16.0f, true, true };
				_normal_combo_2_l = make_shared<Flipbook>("_normal_combo_2_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_2_left.png", info);
				_normal_combo_2_l->Init();
				RESOURCE.AddResource(_normal_combo_2_l);

				_normal_combo_2_r = make_shared<Flipbook>("_normal_combo_2_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_2_right.png", info);
				_normal_combo_2_r->Init();
				RESOURCE.AddResource(_normal_combo_2_r);
			}

			// Combo #3
			{
				FlipbookInfo info{ 1, 9, 0, 0, 8, 16.0f, true, true };
				_normal_combo_3_l = make_shared<Flipbook>("_normal_combo_3_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_3_left.png", info);
				_normal_combo_3_l->Init();
				RESOURCE.AddResource(_normal_combo_3_l);

				_normal_combo_3_r = make_shared<Flipbook>("_normal_combo_3_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_combo_3_right.png", info);
				_normal_combo_3_r->Init();
				RESOURCE.AddResource(_normal_combo_3_r);
			}

			// Damaged
			{
				FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
				_normal_damaged_l = make_shared<Flipbook>("_normal_damaged_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_damaged_left.png", info);
				_normal_damaged_l->Init();
				RESOURCE.AddResource(_normal_damaged_l);

				_normal_damaged_r = make_shared<Flipbook>("_normal_damaged_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_damaged_right.png", info);
				_normal_damaged_r->Init();
				RESOURCE.AddResource(_normal_damaged_r);
			}

			// Dash
			{
				FlipbookInfo info{ 1, 6, 0, 0, 5, 16.0f, true, true };
				_normal_dash_l = make_shared<Flipbook>("_normal_dash_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_dash_forward_left.png", info);
				_normal_dash_l->Init();
				RESOURCE.AddResource(_normal_dash_l);

				_normal_dash_r = make_shared<Flipbook>("_normal_dash_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_dash_forward_right.png", info);
				_normal_dash_r->Init();
				RESOURCE.AddResource(_normal_dash_r);
			}

			// Died
			{
				FlipbookInfo info{ 1, 10, 0, 0, 9, 16.0f, true, true };
				_normal_died_l = make_shared<Flipbook>("_normal_died_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_died_left.png", info);
				_normal_died_l->Init();
				RESOURCE.AddResource(_normal_died_l);

				_normal_died_r = make_shared<Flipbook>("_normal_died_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_died_right.png", info);
				_normal_died_r->Init();
				RESOURCE.AddResource(_normal_died_r);
			}

			// Fall
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_normal_fall_l = make_shared<Flipbook>("_normal_fall_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_fall_left.png", info);
				_normal_fall_l->Init();
				RESOURCE.AddResource(_normal_fall_l);

				_normal_fall_r = make_shared<Flipbook>("_normal_fall_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_fall_right.png", info);
				_normal_fall_r->Init();
				RESOURCE.AddResource(_normal_fall_r);
			}

			// Idle
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_normal_idle_l = make_shared<Flipbook>("_normal_idle_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_idle_left.png", info);
				_normal_idle_l->Init();
				RESOURCE.AddResource(_normal_idle_l);

				_normal_idle_r = make_shared<Flipbook>("_normal_idle_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_idle_right.png", info);
				_normal_idle_r->Init();
				RESOURCE.AddResource(_normal_idle_r);
			}

			// Jump
			{
				FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
				_normal_jump_l = make_shared<Flipbook>("_normal_jump_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_jump_left.png", info);
				_normal_jump_l->Init();
				RESOURCE.AddResource(_normal_jump_l);

				_normal_jump_r = make_shared<Flipbook>("_normal_jump_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_jump_right.png", info);
				_normal_jump_r->Init();
				RESOURCE.AddResource(_normal_jump_r);
			}

			// Run
			{
				FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
				_normal_run_l = make_shared<Flipbook>("_normal_run_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_run_left.png", info);
				_normal_run_l->Init();
				RESOURCE.AddResource(_normal_run_l);

				_normal_run_r = make_shared<Flipbook>("_normal_run_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_run_right.png", info);
				_normal_run_r->Init();
				RESOURCE.AddResource(_normal_run_r);
			}

			// Slide
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_normal_slide_l = make_shared<Flipbook>("_normal_slide_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_slide_left.png", info);
				_normal_slide_l->Init();
				RESOURCE.AddResource(_normal_slide_l);

				_normal_slide_r = make_shared<Flipbook>("_normal_slide_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_slide_right.png", info);
				_normal_slide_r->Init();
				RESOURCE.AddResource(_normal_slide_r);
			}

			// Walk
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_normal_walk_l = make_shared<Flipbook>("_normal_walk_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_walk_left.png", info);
				_normal_walk_l->Init();
				RESOURCE.AddResource(_normal_walk_l);

				_normal_walk_r = make_shared<Flipbook>("_normal_walk_r", "../Resources/Images/Flipbooks/Player_normal/FB_Player_walk_right.png", info);
				_normal_walk_r->Init();
				RESOURCE.AddResource(_normal_walk_r);
			}

			// Wallslide
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_normal_wallslide_l = make_shared<Flipbook>("_normal_wallslide_l", "../Resources/Images/Flipbooks/Player_normal/FB_Player_wallslide_left.png", info);
				_normal_wallslide_l->Init();
				RESOURCE.AddResource(_normal_wallslide_l);

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
				_gun_air_attack_l = make_shared<Flipbook>("_gun_air_attack_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_air_attack_left.png", info);
				_gun_air_attack_l->Init();
				RESOURCE.AddResource(_gun_air_attack_l);

				_gun_air_attack_r = make_shared<Flipbook>("_gun_air_attack_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_air_attack_right.png", info);
				_gun_air_attack_r->Init();
				RESOURCE.AddResource(_gun_air_attack_r);
			}

			// Damage
			{
				FlipbookInfo info{ 1, 4, 0, 0, 3, 16.0f, true, true };
				_gun_damaged_l = make_shared<Flipbook>("_gun_damaged_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_damaged_left.png", info);
				_gun_damaged_l->Init();
				RESOURCE.AddResource(_gun_damaged_l);

				_gun_damaged_r = make_shared<Flipbook>("_gun_damaged_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_damaged_right.png", info);
				_gun_damaged_r->Init();
				RESOURCE.AddResource(_gun_damaged_r);
			}

			// Dash
			{
				FlipbookInfo info{ 1, 6, 0, 0, 5, 16.0f, true, true };
				_gun_dash_l = make_shared<Flipbook>("_gun_dash_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_dash_left.png", info);
				_gun_dash_l->Init();
				RESOURCE.AddResource(_gun_dash_l);

				_gun_dash_r = make_shared<Flipbook>("_gun_dash_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_dash_right.png", info);
				_gun_dash_r->Init();
				RESOURCE.AddResource(_gun_dash_r);
			}

			// Died
			{
				FlipbookInfo info{ 1, 10, 0, 0, 9, 16.0f, true, true };
				_gun_died_l = make_shared<Flipbook>("_gun_died_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_died_left.png", info);
				_gun_died_l->Init();
				RESOURCE.AddResource(_gun_died_l);

				_gun_died_r = make_shared<Flipbook>("_gun_died_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_died_right.png", info);
				_gun_died_r->Init();
				RESOURCE.AddResource(_gun_died_r);
			}

			// Idle
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_idle_l = make_shared<Flipbook>("_gun_idle_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_idle_left.png", info);
				_gun_idle_l->Init();
				RESOURCE.AddResource(_gun_idle_l);

				_gun_idle_r = make_shared<Flipbook>("_gun_idle_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_idle_right.png", info);
				_gun_idle_r->Init();
				RESOURCE.AddResource(_gun_idle_r);
			}

			// Jump
			{
				FlipbookInfo info{ 1, 5, 0, 0, 4, 16.0f, true, true };
				_gun_jump_l = make_shared<Flipbook>("_gun_jump_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_jump_left.png", info);
				_gun_jump_l->Init();
				RESOURCE.AddResource(_gun_jump_l);

				_gun_jump_r = make_shared<Flipbook>("_gun_jump_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_jump_right.png", info);
				_gun_jump_r->Init();
				RESOURCE.AddResource(_gun_jump_r);
			}

			// Run
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_run_l = make_shared<Flipbook>("_gun_run_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_run_left.png", info);
				_gun_run_l->Init();
				RESOURCE.AddResource(_gun_jump_l);

				_gun_run_r = make_shared<Flipbook>("_gun_run_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_run_right.png", info);
				_gun_run_r->Init();
				RESOURCE.AddResource(_gun_run_r);
			}

			// Shot
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_gun_shot_l = make_shared<Flipbook>("_gun_shot_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_shot_left.png", info);
				_gun_shot_l->Init();
				RESOURCE.AddResource(_gun_shot_l);

				_gun_shot_r = make_shared<Flipbook>("_gun_shot_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_shot_right.png", info);
				_gun_shot_r->Init();
				RESOURCE.AddResource(_gun_shot_r);
			}

			// Slide
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_slide_l = make_shared<Flipbook>("_gun_slide_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_slide_left.png", info);
				_gun_slide_l->Init();
				RESOURCE.AddResource(_gun_slide_l);

				_gun_slide_r = make_shared<Flipbook>("_gun_slide_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_slide_right.png", info);
				_gun_slide_r->Init();
				RESOURCE.AddResource(_gun_slide_r);
			}

			// Walk
			{
				FlipbookInfo info{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_gun_walk_l = make_shared<Flipbook>("_gun_slide_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_walk_left.png", info);
				_gun_walk_l->Init();
				RESOURCE.AddResource(_gun_walk_l);

				_gun_walk_r = make_shared<Flipbook>("_gun_walk_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_walk_right.png", info);
				_gun_walk_r->Init();
				RESOURCE.AddResource(_gun_walk_r);
			}

			// Wallslide
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_gun_wallslide_l = make_shared<Flipbook>("_gun_wallslide_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_wallslide_left.png", info);
				_gun_wallslide_l->Init();
				RESOURCE.AddResource(_gun_wallslide_l);

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
				_sword_air_attack_l = make_shared<Flipbook>("_sword_air_attack_l", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_air_attack_left.png", info);
				_sword_air_attack_l->Init();
				RESOURCE.AddResource(_sword_air_attack_l);

				_sword_air_attack_r = make_shared<Flipbook>("_sword_air_attack_r", "../Resources/Images/Flipbooks/Player_sword/FB_Player_Sword_air_attack_right.png", info);
				_sword_air_attack_r->Init();
				RESOURCE.AddResource(_sword_air_attack_r);
			}

			// Combo #1
			{
				FlipbookInfo info{ 1, 2, 0, 0, 1, 16.0f, true, true };
				_sword_combo_1_l = make_shared<Flipbook>("_sword_combo_1_l", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_air_attack_left.png", info);
				_sword_combo_1_l->Init();
				RESOURCE.AddResource(_sword_combo_1_l);

				_sword_combo_1_r = make_shared<Flipbook>("_sword_combo_1_r", "../Resources/Images/Flipbooks/Player_gun/FB_Player_Gun_air_attack_right.png", info);
				_sword_combo_1_r->Init();
				RESOURCE.AddResource(_sword_combo_1_r);
			}

			#pragma endregion
		}
	}

	// Load Prefabs
	{
		_ground = make_shared<Ground>();
		_ground->SetRenderPass(_textureRenderPass);

		_background1 = make_shared<Background1>();
		_background1->SetRenderPass(_textureRenderPass);

		_background2 = make_shared<Background2>();
		_background2->SetRenderPass(_textureRenderPass);

		_sideWall = make_shared<SideWall>();
		_sideWall->SetRenderPass(_textureRenderPass);

		_house1 = make_shared<House1>();
		_house1->SetRenderPass(_textureRenderPass);

		_house2 = make_shared<House2>();
		_house2->SetRenderPass(_textureRenderPass);

		_bush = make_shared<Bush>();
		_bush->SetRenderPass(_textureRenderPass);
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
		_uiRenderPass = make_shared<RenderPass>();
		_uiRenderPass->SetShader(_textShader);
		_uiRenderPass->SetCamera(_uiCameraComponent);

		_textureRenderPass = make_shared<RenderPass>();
		_textureRenderPass->SetShader(_textureShader);
		_textureRenderPass->SetCamera(_mainCameraComponent);
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
			auto background1_2 = _background1->Instantiate("Background1_2", { 1000.0f, -150.0f, 0.f });
			_gameObjects.push_back(background1_2);
			auto background1_3 = _background1->Instantiate("Background1_3", { 2000.0f, -150.0f, 0.f });
			_gameObjects.push_back(background1_3);

			auto background2_1 = _background2->Instantiate("Background2_1", { 0.0f, -200.0f, 0.f });
			_gameObjects.push_back(background2_1);
			auto background2_2 = _background2->Instantiate("Background2_2", { 1000.0f, -200.0f, 0.f });
			_gameObjects.push_back(background2_2);
			auto background2_3 = _background2->Instantiate("Background2_3", { 2000.0f, -200.0f, 0.f });
			_gameObjects.push_back(background2_3);

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

			auto ground_1 = _ground->Instantiate("Ground1", { -700.0f, -320.0f, 0.f });
			_gameObjects.push_back(ground_1);
			auto ground_2 = _ground->Instantiate("Ground2", { 0.0f, -320.0f, 0.f });
			_gameObjects.push_back(ground_2);
			auto ground_3 = _ground->Instantiate("Ground3", { 760.0f, -320.0f, 0.f });
			_gameObjects.push_back(ground_3);
			auto ground_4 = _ground->Instantiate("Ground4", { 1520, -320.0f, 0.f });
			_gameObjects.push_back(ground_4);
			auto ground_5 = _ground->Instantiate("Ground4", { 2200.0f, -320.0f, 0.f });
			_gameObjects.push_back(ground_5);
			auto ground_6 = _ground->Instantiate("Ground4", { 2700.0f, -320.0f, 0.f });
			_gameObjects.push_back(ground_6);
		}

		// Buildings
		{
			auto house1 = _house1->Instantiate("House1", { 400.0f, 45.0f, 0.0f });
			_gameObjects.push_back(house1);

			auto house2 = _house2->Instantiate("House2", { -200.0f, -35.0f, 0.0f });
			_gameObjects.push_back(house2);

			auto sideWall = _sideWall->Instantiate("SideWall", { -550.0f, 200.0f, 0.0f }, glm::vec3(0.0f), glm::vec3(0.5f, 0.65f, 0.5f));
			_gameObjects.push_back(sideWall);
		}
	}

#pragma region PRESENT_RENDER_PASSES
	RENDER.AddRenderPass(_textureRenderPass);
	RENDER.AddRenderPass(_uiRenderPass);
#pragma endregion

#pragma region PLAY_BGM
	AUDIO.PlayBGM("PowerUp");
#pragma endregion

#pragma endregion
}

