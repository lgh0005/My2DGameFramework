#include "pch.h"
#include "Lobby.h"

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
#include "UIBlocker.h"
#include "CharacterController.h"
#include "StartButtonScript.h"
#include "OptionButtonScript.h"
#include "QuitButtonScript.h"
#pragma endregion

Lobby::Lobby(const string& name) : Super(name) {}

void Lobby::CreateRenderProperties()
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

	// Load SettingUI shader
	{
		_SettingUIShader = make_shared<Shader>("SettingUIShader", "../Resources/Shaders/SettingUI.vert", "../Resources/Shaders/SettingUI.frag");
		_SettingUIShader->Init();
		_SettingUIShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_SettingUIShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_SettingUIShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_SettingUIShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		RESOURCE.AddResource(_SettingUIShader);
	}

	// Load Character shader
	{
		_CharacterShader = make_shared<Shader>("CharacterShader", "../Resources/Shaders/Character.vert", "../Resources/Shaders/Character.frag");
		_CharacterShader->Init();
		_CharacterShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_CharacterShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_CharacterShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_CharacterShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		_CharacterShader->AddUniform("flip");
		RESOURCE.AddResource(_CharacterShader);

		_CharacterUniforms = make_shared<UniformSet>("CharacterUniforms");
		_CharacterUniforms->Set("flip", false);
		RESOURCE.AddResource(_CharacterUniforms);
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

		_SettingUIRenderPass = make_shared<RenderPass>();
		_SettingUIRenderPass->SetShader(_SettingUIShader);
		_SettingUIRenderPass->SetCamera(_uiCameraComponent);

		_CharacterRenderPass = make_shared<RenderPass>();
		_CharacterRenderPass->SetShader(_CharacterShader);
		_CharacterRenderPass->SetCamera(_mainCameraComponent);
		_CharacterRenderPass->SetUniformSet(_CharacterUniforms);
	}
}

void Lobby::LoadResources()
{
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

			// Flipbooks
			{
				FlipbookInfo info1{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_characterIdleRightFlipbook = make_shared<Flipbook>("Character_Idle_right", "../Resources/Images/Flipbooks/Player_normal/FB_Player_idle_right.png", info1);
				_characterIdleRightFlipbook->Init();
				RESOURCE.AddResource(_characterIdleRightFlipbook);

				FlipbookInfo info2{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_characterIdleLeftFlipbook = make_shared<Flipbook>("Character_Idle_left", "../Resources/Images/Flipbooks/Player_normal/FB_Player_idle_left.png", info2);
				_characterIdleLeftFlipbook->Init();
				RESOURCE.AddResource(_characterIdleLeftFlipbook);

				FlipbookInfo info3{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_characterWalkLeftFlipbook = make_shared<Flipbook>("Character_Walk_right", "../Resources/Images/Flipbooks/Player_normal/FB_Player_walk_right.png", info3);
				_characterWalkLeftFlipbook->Init();
				RESOURCE.AddResource(_characterWalkLeftFlipbook);

				FlipbookInfo info4{ 1, 8, 0, 0, 7, 16.0f, true, true };
				_characterWalkRightFlipbook = make_shared<Flipbook>("Character_Walk_left", "../Resources/Images/Flipbooks/Player_normal/FB_Player_walk_left.png", info4);
				_characterWalkRightFlipbook->Init();
				RESOURCE.AddResource(_characterWalkRightFlipbook);
			}

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

			_gameTitleText1 = make_shared<Font>("Title1", "../Resources/Fonts/Gamer.ttf", "Stickman", 180, Colors::Black);
			_gameTitleText1->Init();
			RESOURCE.AddResource(_gameTitleText1);

			_gameTitleText2 = make_shared<Font>("Title2", "../Resources/Fonts/Gamer.ttf", "Survivor", 175, Colors::Black);
			_gameTitleText2->Init();
			RESOURCE.AddResource(_gameTitleText2);

			_buttonText1 = make_shared<Font>("Start", "../Resources/Fonts/Gamer.ttf", "Start", 70, Colors::Black);
			_buttonText1->Init();
			RESOURCE.AddResource(_buttonText1);

			_buttonText2 = make_shared<Font>("Option", "../Resources/Fonts/Gamer.ttf", "Option", 64, Colors::Black);
			_buttonText2->Init();
			RESOURCE.AddResource(_buttonText2);

			_buttonText3 = make_shared<Font>("Quit", "../Resources/Fonts/Gamer.ttf", "Quit", 64, Colors::Black);
			_buttonText3->Init();
			RESOURCE.AddResource(_buttonText3);

			_buttonTextureNormal = make_shared<Texture>("Button_Normal", "../Resources/Images/UIs/Button.png");
			_buttonTextureNormal->Init();
			RESOURCE.AddResource(_buttonTextureNormal);

			_buttonTextureSelect = make_shared<Texture>("Button_Select", "../Resources/Images/UIs/Button_selected.png");
			_buttonTextureSelect->Init();
			RESOURCE.AddResource(_buttonTextureSelect);

			_lobbyBGM = make_shared<BGM>("DadnMe", "../Resources/Audio/BGM/dadnme.wav", FMOD_LOOP_NORMAL);
			AUDIO.AddBGM(_lobbyBGM);

			_lobbySFX = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/whoosh2.wav", FMOD_LOOP_OFF);
			AUDIO.AddSFX(_lobbySFX);
		}
	
		// Settings UI
		{
			_uiPanel = make_shared<Texture>("UIPanel", "../Resources/Images/UIs/UI_Panel.png");
			_uiPanel->Init();
			RESOURCE.AddResource(_uiPanel);

			_uiToggle = make_shared<Texture>("UIToggle", "../Resources/Images/UIs/toggle.png");
			_uiToggle->Init();
			RESOURCE.AddResource(_uiToggle);

			_uiToggleSelected = make_shared<Texture>("UIToggleSelected", "../Resources/Images/UIs/toggle_selected.png");
			_uiToggleSelected->Init();
			RESOURCE.AddResource(_uiToggleSelected);

			_checkIcon = make_shared<Texture>("UICheck", "../Resources/Images/UIs/check.png");
			_checkIcon->Init();
			RESOURCE.AddResource(_checkIcon);

			_backIcon = make_shared<Texture>("UIBack", "../Resources/Images/UIs/back.png");
			_backIcon->Init();
			RESOURCE.AddResource(_backIcon);

			_bgmText = make_shared<Font>("bgm", "../Resources/Fonts/Gamer.ttf", "BGM", 128, Colors::Black);
			_bgmText->Init();
			RESOURCE.AddResource(_bgmText);

			_sfxText = make_shared<Font>("sfx", "../Resources/Fonts/Gamer.ttf", "SFX", 128, Colors::Black);
			_sfxText->Init();
			RESOURCE.AddResource(_sfxText);
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

		_character = make_shared<Character>();
		_character->SetRenderPass(_CharacterRenderPass);

		_sideWall = make_shared<SideWall>();
		_sideWall->SetRenderPass(_textureRenderPass);

		_house1 = make_shared<House1>();
		_house1->SetRenderPass(_textureRenderPass);

		_house2 = make_shared<House2>();
		_house2->SetRenderPass(_textureRenderPass);

		_bush = make_shared<Bush>();
		_bush->SetRenderPass(_textureRenderPass);

		_settingUI = make_shared<UISetting>();
		_settingUI->SetRenderPass(_SettingUIRenderPass);
		_settingUI->SetCurrentScene(shared_from_this());
	}
}

void Lobby::CreateSceneContext()
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
		auto background1 = _background1->Instantiate("Background1", { 0.0f, -150.0f, 0.f });
		_gameObjects.push_back(background1);

		auto background2 = _background2->Instantiate("Background2", { 0.0f, -200.0f, 0.f });
		_gameObjects.push_back(background2);

		auto bush1 = _bush->Instantiate("Bush1", { -384.0f, -140.0f, 0.0f });
		_gameObjects.push_back(bush1);

		auto bush2 = _bush->Instantiate("Bush2", { 0.0f, -140.0f, 0.0f });
		_gameObjects.push_back(bush2);

		auto house1 = _house1->Instantiate("House1", { 400.0f, 45.0f, 0.0f });
		_gameObjects.push_back(house1);

		auto house2 = _house2->Instantiate("House2", { -200.0f, -35.0f, 0.0f });
		_gameObjects.push_back(house2);

		auto ground_1 = _ground->Instantiate("Ground1", { -384.0f, -320.0f, 0.f });
		_gameObjects.push_back(ground_1);

		auto ground_2 = _ground->Instantiate("Ground2", { 384.0f, -320.0f, 0.f });
		_gameObjects.push_back(ground_2);

		auto sideWall = _sideWall->Instantiate("SideWall", { -550.0f, 200.0f, 0.0f }, glm::vec3(0.0f), glm::vec3(0.5f, 0.65f, 0.5f));
		_gameObjects.push_back(sideWall);

		auto character = _character->Instantiate("Character", { -300.0f, -140.0f, 0.0f });
		_gameObjects.push_back(character);
	}

	// Setting
	{
		auto setting = _settingUI->Instantiate("SettingUI", { 0.0f, 0.0f, 0.0f });
		_gameObjects.push_back(setting);
	}

	// UI
	{
		// UI Blocker
		{
			_uiBlocker = make_shared<GameObject>("UIBlocker");
			_uiBlockerTransform = make_shared<Transform>
				(
					"DummyTransform",
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_uiBlocker->SetTransform(_uiBlockerTransform);
			_uiBlockerScript = make_shared<UIBlocker>("UIBlocker");
			_uiBlockerScript->SetCurrentScene(shared_from_this());
			_uiBlocker->AddBehaviour(_uiBlockerScript);
			_gameObjects.push_back(_uiBlocker);
		}

		// Title Text #1
		{
			_gameTitleTextTexture1 = make_shared<UIText>("Title1", _uiCameraComponent, _gameTitleText1);
			_gameTitleTextTransform1 = make_shared<Transform>
				(
					"TitleText1",
					glm::vec3(0.0f, 320.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_gameTitleGameObject1 = make_shared<GameObject>("Title1");
			_gameTitleGameObject1->SetTransform(_gameTitleTextTransform1);
			_gameTitleGameObject1->AddRenderable(static_pointer_cast<IRenderable>(_gameTitleTextTexture1));
			_uiRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_gameTitleTextTexture1));
			_gameObjects.push_back(_gameTitleGameObject1);
		}

		// Title Text #2
		{
			_gameTitleTextTexture2 = make_shared<UIText>("Title2", _uiCameraComponent, _gameTitleText2);
			_gameTitleTextTransform2 = make_shared<Transform>
				(
					"TitleText2",
					glm::vec3(0.0f, 220.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_gameTitleGameObject2 = make_shared<GameObject>("Title2");
			_gameTitleGameObject2->SetTransform(_gameTitleTextTransform2);
			_gameTitleGameObject2->AddRenderable(static_pointer_cast<IRenderable>(_gameTitleTextTexture2));
			_uiRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_gameTitleTextTexture2));
			_gameObjects.push_back(_gameTitleGameObject2);
		}

		// Button #1
		{
			_buttonText1Texture = make_shared<UIText>("Start", _uiCameraComponent, _buttonText1);
			_button1 = make_shared<UIButton>
				(
					"StartButton",
					_uiCameraComponent,
					_buttonTextureNormal,
					glm::vec2(260.0f, 81.0f),
					Inputs::Mouse::Left
				);

			_buttonTransform1 = make_shared<Transform>
				(
					"ButtonTransform",
					glm::vec3(0.0f, 60.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_buttonGameObject1 = make_shared<GameObject>("ButtonObject1");
			_buttonGameObject1->SetTransform(_buttonTransform1);
			_buttonGameObject1->AddRenderable(static_pointer_cast<IRenderable>(_button1));
			_buttonGameObject1->AddRenderable(static_pointer_cast<IRenderable>(_buttonText1Texture));
			_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_button1));
			_uiRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_buttonText1Texture));
			_buttonScript1 = make_shared<StartButtonScript>("StartButtonScript");
			_buttonGameObject1->AddBehaviour(_buttonScript1);
			_buttonScript1->SetCurrentScene(shared_from_this());
			_gameObjects.push_back(_buttonGameObject1);
		}

		// Button #2
		{
			_buttonText2Texture = make_shared<UIText>("Option", _uiCameraComponent, _buttonText2);
			_button2 = make_shared<UIButton>
				(
					"OptionButton",
					_uiCameraComponent,
					_buttonTextureNormal,
					glm::vec2(260.0f, 81.0f),
					Inputs::Mouse::Left
				);

			_buttonTransform2 = make_shared<Transform>
				(
					"ButtonTransform",
					glm::vec3(0.0f, -40.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_buttonGameObject2 = make_shared<GameObject>("ButtonObject2");
			_buttonGameObject2->SetTransform(_buttonTransform2);
			_buttonGameObject2->AddRenderable(static_pointer_cast<IRenderable>(_button2));
			_buttonGameObject2->AddRenderable(static_pointer_cast<IRenderable>(_buttonText2Texture));
			_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_button2));
			_uiRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_buttonText2Texture));
			_buttonScript2 = make_shared<OptionButtonScript>("OptionButtonScript");
			_buttonScript2->SetCurrentScene(shared_from_this());
			_buttonGameObject2->AddBehaviour(_buttonScript2);
			_buttonScript2->SetCurrentScene(shared_from_this());
			_gameObjects.push_back(_buttonGameObject2);
		}

		// Button #3
		{
			_buttonText3Texture = make_shared<UIText>("Quit", _uiCameraComponent, _buttonText3);
			_button3 = make_shared<UIButton>
				(
					"QuitButton",
					_uiCameraComponent,
					_buttonTextureNormal,
					glm::vec2(260.0f, 81.0f),
					Inputs::Mouse::Left
				);

			_buttonTransform3 = make_shared<Transform>
				(
					"ButtonTransform",
					glm::vec3(0.0f, -140.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_buttonGameObject3 = make_shared<GameObject>("ButtonObject3");
			_buttonGameObject3->SetTransform(_buttonTransform3);
			_buttonGameObject3->AddRenderable(static_pointer_cast<IRenderable>(_button3));
			_buttonGameObject3->AddRenderable(static_pointer_cast<IRenderable>(_buttonText3Texture));
			_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_button3));
			_uiRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_buttonText3Texture));
			_buttonScript3 = make_shared<QuitButtonScript>("QuitButtonScript");
			_buttonGameObject3->AddBehaviour(_buttonScript3);
			_buttonScript3->SetCurrentScene(shared_from_this());
			_gameObjects.push_back(_buttonGameObject3);
		}

		// Canvas
		{
			_uiCanvas = make_shared<UICanvas>("MainUICanvas", _uiCameraComponent, glm::vec2(300.0f, 200.0f));
			_uiCanvasTransform = make_shared<Transform>
				(
					"MainUICanvas",
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_uiCanvasObject = make_shared<GameObject>("MainUICanvas");
			_uiCanvasObject->SetTransform(_uiCanvasTransform);
			_uiCanvasObject->AddComponent(_uiCanvas);
			_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_button1));
			_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_button2));
			_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_button3));
			_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_gameTitleTextTexture1));
			_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_gameTitleTextTexture2));
			_gameObjects.push_back(_uiCanvasObject);
		}
	}

#pragma endregion

#pragma region PRESENT_RENDER_PASSES
	RENDER.AddRenderPass(_textureRenderPass);
	RENDER.AddRenderPass(_CharacterRenderPass);
	RENDER.AddRenderPass(_uiRenderPass);
	RENDER.AddRenderPass(_SettingUIRenderPass);
#pragma endregion

#pragma region PLAY_BGM
	AUDIO.PlayBGM("DadnMe");
#pragma endregion
}

