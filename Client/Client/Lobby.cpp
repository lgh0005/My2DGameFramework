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
#include "LobbyUI.h"
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

	shared_ptr<Shader> _SettingUIShader = make_shared<Shader>("SettingUIShader", "../Resources/Shaders/SettingUI.vert", "../Resources/Shaders/SettingUI.frag");
	_SettingUIShader->Init();
	_SettingUIShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_SettingUIShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_SettingUIShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_SettingUIShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	RESOURCE.AddResource(_SettingUIShader);

	shared_ptr<Shader> _CharacterShader = make_shared<Shader>("CharacterShader", "../Resources/Shaders/Character.vert", "../Resources/Shaders/Character.frag");
	_CharacterShader->Init();
	_CharacterShader->AddUniform(Uniforms::UNIFORM_MODEL);
	_CharacterShader->AddUniform(Uniforms::UNIFORM_VIEW);
	_CharacterShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
	_CharacterShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
	_CharacterShader->AddUniform("flip");
	RESOURCE.AddResource(_CharacterShader);
	shared_ptr<UniformSet> _CharacterUniforms = make_shared<UniformSet>("CharacterUniforms");
	_CharacterUniforms->Set("flip", false);
	RESOURCE.AddResource(_CharacterUniforms);

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

	shared_ptr<RenderPass> _SettingUIRenderPass = make_shared<RenderPass>();
	_SettingUIRenderPass->SetShader(_SettingUIShader);
	_SettingUIRenderPass->SetCamera(_uiCameraComponent);
	AddRenderPass("_SettingUIRenderPass", _SettingUIRenderPass);

	shared_ptr<RenderPass> _CharacterRenderPass = make_shared<RenderPass>();
	_CharacterRenderPass->SetShader(_CharacterShader);
	_CharacterRenderPass->SetCamera(_mainCameraComponent);
	_CharacterRenderPass->SetUniformSet(_CharacterUniforms);
	AddRenderPass("_CharacterRenderPass", _CharacterRenderPass);
}

void Lobby::LoadResources()
{
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

	/*===================
	//    Flipbooks    //
	===================*/
	FlipbookInfo info1{ 1, 8, 0, 0, 7, 16.0f, true, true };
	shared_ptr<Flipbook> _characterIdleRightFlipbook = make_shared<Flipbook>("Character_Idle_right", "../Resources/Images/Flipbooks/Player_normal/FB_Player_idle_right.png", info1);
	_characterIdleRightFlipbook->Init();
	RESOURCE.AddResource(_characterIdleRightFlipbook);

	FlipbookInfo info4{ 1, 8, 0, 0, 7, 16.0f, true, true };
	shared_ptr<Flipbook> _characterWalkRightFlipbook = make_shared<Flipbook>("Character_Walk_right", "../Resources/Images/Flipbooks/Player_normal/FB_Player_walk_right.png", info4);
	_characterWalkRightFlipbook->Init();
	RESOURCE.AddResource(_characterWalkRightFlipbook);

	/*===============
	//    Props    //
	===============*/
	shared_ptr<Texture> _sideWallTexture = make_shared<Texture>("SideWall", "../Resources/Images/Extras/sidewall.png");
	_sideWallTexture->Init();
	RESOURCE.AddResource(_sideWallTexture);

	shared_ptr<Texture> _houseTexture1 = make_shared<Texture>("House1", "../Resources/Images/Extras/building2.png");
	_houseTexture1->Init();
	RESOURCE.AddResource(_houseTexture1);

	shared_ptr<Texture> _houseTexture2 = make_shared<Texture>("House2", "../Resources/Images/Extras/house2.png");
	_houseTexture2->Init();
	RESOURCE.AddResource(_houseTexture2);

	shared_ptr<Texture> _bushTexture = make_shared<Texture>("Bush", "../Resources/Images/Extras/grass_foreground.png");
	_bushTexture->Init();
	RESOURCE.AddResource(_bushTexture);

	/*=============
	//    UIs    //
	=============*/
	shared_ptr<Font> _gameTitleText1 = make_shared<Font>("Title1", "../Resources/Fonts/Gamer.ttf", "Stickman", 180, Colors::Black);
	_gameTitleText1->Init();
	RESOURCE.AddResource(_gameTitleText1);

	shared_ptr<Font> _gameTitleText2 = make_shared<Font>("Title2", "../Resources/Fonts/Gamer.ttf", "Survivor", 175, Colors::Black);
	_gameTitleText2->Init();
	RESOURCE.AddResource(_gameTitleText2);

	shared_ptr<Font> _buttonText1 = make_shared<Font>("Start", "../Resources/Fonts/Gamer.ttf", "Start", 70, Colors::Black);
	_buttonText1->Init();
	RESOURCE.AddResource(_buttonText1);

	shared_ptr<Font> _buttonText2 = make_shared<Font>("Option", "../Resources/Fonts/Gamer.ttf", "Option", 64, Colors::Black);
	_buttonText2->Init();
	RESOURCE.AddResource(_buttonText2);

	shared_ptr<Font> _buttonText3 = make_shared<Font>("Quit", "../Resources/Fonts/Gamer.ttf", "Quit", 64, Colors::Black);
	_buttonText3->Init();
	RESOURCE.AddResource(_buttonText3);

	shared_ptr<Texture> _buttonTextureNormal = make_shared<Texture>("Button_Normal", "../Resources/Images/UIs/Button.png");
	_buttonTextureNormal->Init();
	RESOURCE.AddResource(_buttonTextureNormal);

	shared_ptr<Texture> _buttonTextureSelect = make_shared<Texture>("Button_Select", "../Resources/Images/UIs/Button_selected.png");
	_buttonTextureSelect->Init();
	RESOURCE.AddResource(_buttonTextureSelect);

	/*================
	//    Audios    //
	================*/
	shared_ptr<BGM> _lobbyBGM = make_shared<BGM>("DadnMe", "../Resources/Audio/BGM/dadnme.wav", FMOD_LOOP_NORMAL);
	AUDIO.AddBGM(_lobbyBGM);

	shared_ptr<SFX> _lobbySFX = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/whoosh2.wav", FMOD_LOOP_OFF);
	AUDIO.AddSFX(_lobbySFX);
	
	/*====================
	//    Setting UIs   //
	====================*/
	shared_ptr<Texture> _uiPanel = make_shared<Texture>("UIPanel", "../Resources/Images/UIs/UI_Panel.png");
	_uiPanel->Init();
	RESOURCE.AddResource(_uiPanel);

	shared_ptr<Texture> _uiToggle = make_shared<Texture>("UIToggle", "../Resources/Images/UIs/toggle.png");
	_uiToggle->Init();
	RESOURCE.AddResource(_uiToggle);

	shared_ptr<Texture> _uiToggleSelected = make_shared<Texture>("UIToggleSelected", "../Resources/Images/UIs/toggle_selected.png");
	_uiToggleSelected->Init();
	RESOURCE.AddResource(_uiToggleSelected);

	shared_ptr<Texture> _checkIcon = make_shared<Texture>("UICheck", "../Resources/Images/UIs/check.png");
	_checkIcon->Init();
	RESOURCE.AddResource(_checkIcon);

	shared_ptr<Texture> _backIcon = make_shared<Texture>("UIBack", "../Resources/Images/UIs/back.png");
	_backIcon->Init();
	RESOURCE.AddResource(_backIcon);

	shared_ptr<Font> _bgmText = make_shared<Font>("bgm", "../Resources/Fonts/Gamer.ttf", "BGM", 128, Colors::Black);
	_bgmText->Init();
	RESOURCE.AddResource(_bgmText);

	shared_ptr<Font> _sfxText = make_shared<Font>("sfx", "../Resources/Fonts/Gamer.ttf", "SFX", 128, Colors::Black);
	_sfxText->Init();
	RESOURCE.AddResource(_sfxText);

	/*================
	//    Prefabs   //
	================*/
	auto self = shared_from_this();

	shared_ptr<Ground> _ground = make_shared<Ground>("Ground");
	_ground->SetCurrentScene(self);

	shared_ptr<Background1> _background1 = make_shared<Background1>("Background1");
	_background1->SetCurrentScene(self);

	shared_ptr<Background2> _background2 = make_shared<Background2>("Background2");
	_background2->SetCurrentScene(self);

	shared_ptr<Character> _character = make_shared<Character>("Character");
	_character->SetCurrentScene(self);

	shared_ptr<SideWall> _sideWall = make_shared<SideWall>("SideWall");
	_sideWall->SetCurrentScene(self);

	shared_ptr<House1> _house1 = make_shared<House1>("House1");
	_house1->SetCurrentScene(self);

	shared_ptr<House2> _house2 = make_shared<House2>("House2");
	_house2->SetCurrentScene(self);

	shared_ptr<Bush> _bush = make_shared<Bush>("Bush");
	_bush->SetCurrentScene(self);

	shared_ptr<UISetting> _settingUI = make_shared<UISetting>("SettingUI");
	_settingUI->SetCurrentScene(self);
}

void Lobby::CreateSceneContext()
{
	// Set clear color
	RENDER.SetClearColor({ 0.61f, 0.81f, 0.83f, 1.0f });

	// Set render properties
	CreateRenderProperties();

	// Load nessesary resources
	LoadResources();

	/*==============================
	//		MAIN_SCENE_CONTEXT    //
	==============================*/
	auto self = shared_from_this();

	shared_ptr<Background1> _background1 = make_shared<Background1>("Background1");
	_background1->SetCurrentScene(self);
	auto background1 = _background1->Instantiate("Background1", { 0.0f, -150.0f, 0.f });
	_gameObjects.push_back(background1);

	shared_ptr<Background2> _background2 = make_shared<Background2>("Background2");
	_background2->SetCurrentScene(self);
	auto background2 = _background2->Instantiate("Background2", { 0.0f, -200.0f, 0.f });
	_gameObjects.push_back(background2);

	shared_ptr<Bush> _bush = make_shared<Bush>("Bush");
	_bush->SetCurrentScene(self);
	auto bush1 = _bush->Instantiate("Bush1", { -384.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush1);
	auto bush2 = _bush->Instantiate("Bush2", { 0.0f, -140.0f, 0.0f });
	_gameObjects.push_back(bush2);

	shared_ptr<House1> _house1 = make_shared<House1>("House1");
	_house1->SetCurrentScene(self);
	auto house1 = _house1->Instantiate("House1", { 400.0f, 45.0f, 0.0f });
	_gameObjects.push_back(house1);

	shared_ptr<House2> _house2 = make_shared<House2>("House2");
	_house2->SetCurrentScene(self);
	auto house2 = _house2->Instantiate("House2", { -200.0f, -35.0f, 0.0f });
	_gameObjects.push_back(house2);

	shared_ptr<Ground> _ground = make_shared<Ground>("Ground");
	_ground->SetCurrentScene(self);
	auto ground_1 = _ground->Instantiate("Ground1", { -384.0f, -320.0f, 0.f });
	_gameObjects.push_back(ground_1);
	auto ground_2 = _ground->Instantiate("Ground2", { 384.0f, -320.0f, 0.f });
	_gameObjects.push_back(ground_2);

	shared_ptr<SideWall> _sideWall = make_shared<SideWall>("SideWall");
	_sideWall->SetCurrentScene(self);
	auto sideWall = _sideWall->Instantiate("SideWall", { -550.0f, 200.0f, 0.0f }, glm::vec3(0.0f), glm::vec3(0.5f, 0.65f, 0.5f));
	_gameObjects.push_back(sideWall);

	shared_ptr<Character> _character = make_shared<Character>("Character");
	_character->SetCurrentScene(self);
	auto character = _character->Instantiate("Character", { -300.0f, -140.0f, 0.0f });
	_gameObjects.push_back(character);

	shared_ptr<UISetting> _settingUI = make_shared<UISetting>("SettingUI");
	_settingUI->SetCurrentScene(self);
	auto setting = _settingUI->Instantiate("SettingUI", { 0.0f, 0.0f, 0.0f });
	_gameObjects.push_back(setting);

	shared_ptr<LobbyUI> _lobbyUI = make_shared<LobbyUI>("LobbyUI");
	_lobbyUI->SetCurrentScene(self);
	auto lobby = _lobbyUI->Instantiate("LobbyUI", { 0.0f, 0.0f, 0.0f });
	_gameObjects.push_back(lobby);


	// Add RenderPasses to RenderManager
	RENDER.AddRenderPass(GetRenderPass("_textureRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_CharacterRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_textRenderPass"));
	RENDER.AddRenderPass(GetRenderPass("_SettingUIRenderPass"));

	// Play BGM
	AUDIO.PlayBGM("DadnMe");
}

