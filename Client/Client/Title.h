#pragma once
#include "Engine\Scene.h"

class Title : public Scene
{
	using Super = Scene;

public:
	Title(const string& name);
	virtual ~Title() override = default;

protected:
	virtual void CreateSceneContext() override;

private:
	void CreateRenderProperties();
	void LoadResources();

private:
#pragma region GAME_RESOURCES

#pragma region SHADERS
	shared_ptr<Shader> _textureShader;
	shared_ptr<Shader> _textShader;
#pragma endregion

#pragma region TEXTURES
	// Backgrounds
	shared_ptr<Texture> _backgroundTexture1;
	shared_ptr<Texture> _backgroundTexture2;
	shared_ptr<Texture> _ground1;
	shared_ptr<Texture> _ground2;
	shared_ptr<Texture> _bush;
	shared_ptr<Texture> _tree1;
	shared_ptr<Texture> _tree2;
	shared_ptr<Texture> _rocks;

	// Buildings
	shared_ptr<Texture> _building1;
	shared_ptr<Texture> _building2;
	shared_ptr<Texture> _building3;
	shared_ptr<Texture> _house1;
	shared_ptr<Texture> _house2;
	shared_ptr<Texture> _house3;
	shared_ptr<Texture> _sideWall;

	// Props
	shared_ptr<Texture> _ladder;
	shared_ptr<Texture> _bullet;
	shared_ptr<Texture> _gunTex;
	shared_ptr<Texture> _sword;

	// UIs
	shared_ptr<Texture> _button;
	shared_ptr<Texture> _buttonSelected;
	shared_ptr<Texture> _toggle;
	shared_ptr<Texture> _toggleSelected;
	shared_ptr<Texture> _panel;
	shared_ptr<Texture> _iconBack;
	shared_ptr<Texture> _iconCheck;
	shared_ptr<Texture> _health;
#pragma endregion

#pragma region AUDIOS
	shared_ptr<BGM> _lobbyBGM;
	shared_ptr<BGM> _inGameBGM;

	shared_ptr<SFX> _gunSFX;
	shared_ptr<SFX> _punch1;
	shared_ptr<SFX> _punch2;
	shared_ptr<SFX> _punch3;
	shared_ptr<SFX> _sword1;
	shared_ptr<SFX> _sword2;
	shared_ptr<SFX> _sword3;
	shared_ptr<SFX> _sword4;
	shared_ptr<SFX> _sword5;
	shared_ptr<SFX> _whoosh1;
	shared_ptr<SFX> _whoosh2;
#pragma endregion

#pragma endregion
};

