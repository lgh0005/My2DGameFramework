#include "pch.h"
#include "Title.h"

Title::Title(const string& name) : Super(name)
{

}

void Title::CreateRenderProperties()
{
	// Load _textureShader
	{
		_textureShader = make_shared<Shader>("TextureShader", "../Resources/Shaders/default.vert", "../Resources/Shaders/default.frag");
		_textureShader->Init();
		_textureShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_textureShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_textureShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_textureShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		RESOURCE.AddResource(_textureShader);
	}

	// Load _textShader
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
}

void Title::LoadResources()
{
	// Load Textures
	{
		_backgroundTexture1 = make_shared<Texture>("Background1", "../Resources/Images/Extras/background2.png");
		_backgroundTexture1->Init();
		RESOURCE.AddResource(_backgroundTexture1);

		_backgroundTexture2 = make_shared<Texture>("Background2", "../Resources/Images/Extras/background1.png");
		_backgroundTexture2->Init();
		RESOURCE.AddResource(_backgroundTexture2);

		_ground1 = make_shared<Texture>("Ground", "../Resources/Images/Extras/groundBig.png");
		_ground1->Init();
		RESOURCE.AddResource(_ground1);

		_ground2 = make_shared<Texture>("Ground2", "../Resources/Images/Extras/ground.png");
		_ground2->Init();
		RESOURCE.AddResource(_ground2);

		_bush = make_shared<Texture>("Bush", "../Resources/Images/Extras/grass_foreground.png");
		_bush->Init();
		RESOURCE.AddResource(_bush);

		_tree1 = make_shared<Texture>("Tree1", "../Resources/Images/Extras/tree1.png");
		_tree1->Init();
		RESOURCE.AddResource(_tree1);

		_tree2 = make_shared<Texture>("Tree1", "../Resources/Images/Extras/tree2.png");
		_tree2->Init();
		RESOURCE.AddResource(_tree2);

		_rocks = make_shared<Texture>("Tree1", "../Resources/Images/Extras/rocks.png");
		_rocks->Init();
		RESOURCE.AddResource(_rocks);

		_building1 = make_shared<Texture>("Building1", "../Resources/Images/Extras/building1.png");
		_building1->Init();
		RESOURCE.AddResource(_building1);

		_building2 = make_shared<Texture>("Building2", "../Resources/Images/Extras/building2.png");
		_building2->Init();
		RESOURCE.AddResource(_building2);

		_building3 = make_shared<Texture>("Building3", "../Resources/Images/Extras/building3.png");
		_building3->Init();
		RESOURCE.AddResource(_building3);

		_house1 = make_shared<Texture>("House1", "../Resources/Images/Extras/house1.png");
		_house1->Init();
		RESOURCE.AddResource(_house1);

		_house2 = make_shared<Texture>("House2", "../Resources/Images/Extras/house2.png");
		_house2->Init();
		RESOURCE.AddResource(_house2);

		_house3 = make_shared<Texture>("House3", "../Resources/Images/Extras/house3.png");
		_house3->Init();
		RESOURCE.AddResource(_house3);

		_sideWall = make_shared<Texture>("SideWall", "../Resources/Images/Extras/sidewall.png");
		_sideWall->Init();
		RESOURCE.AddResource(_sideWall);

		_ladder = make_shared<Texture>("Ladder", "../Resources/Images/Props/ladder.png");
		_ladder->Init();
		RESOURCE.AddResource(_ladder);

		_bullet = make_shared<Texture>("Ladder", "../Resources/Images/Props/bullet.png");
		_bullet->Init();
		RESOURCE.AddResource(_bullet);

		_gunTex = make_shared<Texture>("Gun", "../Resources/Images/Props/gun.png");
		_gunTex->Init();
		RESOURCE.AddResource(_gunTex);

		_sword = make_shared<Texture>("Sword", "../Resources/Images/Props/sword.png");
		_sword->Init();
		RESOURCE.AddResource(_sword);

		_button = make_shared<Texture>("Button", "../Resources/Images/UIs/Button.png");
		_button->Init();
		RESOURCE.AddResource(_button);

		_buttonSelected = make_shared<Texture>("Button_Selected", "../Resources/Images/UIs/Button_selected.png");
		_buttonSelected->Init();
		RESOURCE.AddResource(_buttonSelected);

		_toggle = make_shared<Texture>("Toggle", "../Resources/Images/UIs/toggle.png");
		_toggle->Init();
		RESOURCE.AddResource(_toggle);

		_toggleSelected = make_shared<Texture>("Toggle_Selected", "../Resources/Images/UIs/toggle_selected.png");
		_toggleSelected->Init();
		RESOURCE.AddResource(_toggleSelected);

		_panel = make_shared<Texture>("Panel", "../Resources/Images/UIs/UI_Panel.png");
		_panel->Init();
		RESOURCE.AddResource(_panel);

		_iconBack = make_shared<Texture>("Panel", "../Resources/Images/UIs/back.png");
		_iconBack->Init();
		RESOURCE.AddResource(_iconBack);

		_iconCheck = make_shared<Texture>("Panel", "../Resources/Images/UIs/check.png");
		_iconCheck->Init();
		RESOURCE.AddResource(_iconCheck);

		_health = make_shared<Texture>("Panel", "../Resources/Images/UIs/health.png");
		_health->Init();
		RESOURCE.AddResource(_health);
	}

	// Load Audios
	{
		_lobbyBGM = make_shared<BGM>("DadnMe", "../Resources/Audio/BGM/dadnme.wav", FMOD_LOOP_NORMAL);
		AUDIO.AddBGM(_lobbyBGM);

		_inGameBGM = make_shared<BGM>("PowerUp", "../Resources/Audio/BGM/power_up.mp3", FMOD_LOOP_NORMAL);
		AUDIO.AddBGM(_inGameBGM);

		_gunSFX = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/punch1.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_gunSFX);

		_punch1 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/gun.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_punch1);

		_punch2 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/punch2.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_punch2);

		_punch3 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/punch3.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_punch3);

		_sword1 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/sword1.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_sword1);

		_sword2 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/sword2.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_sword2);

		_sword3 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/sword3.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_sword3);

		_sword4 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/sword4.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_sword4);

		_sword5 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/sword5.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_sword5);

		_whoosh1 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/whoosh1.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_whoosh1);

		_whoosh2 = make_shared<SFX>("ButtonSFX", "../Resources/Audio/SFX/whoosh2.wav", FMOD_LOOP_OFF);
		AUDIO.AddSFX(_whoosh2);
	}
}

void Title::CreateSceneContext()
{
	// Set clear color
	RENDER.SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

	// Set render properties
	CreateRenderProperties();

	// Load nessesary resources
	LoadResources();

	SCENE.LoadScene("Lobby");
}