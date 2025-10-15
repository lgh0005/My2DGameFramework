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
class LobbyUI;
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
	virtual void LoadResources() override;
	virtual void CreateRenderProperties() override;
	virtual void CreateSceneContext() override;
};

