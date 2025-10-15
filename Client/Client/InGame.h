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
class Enemy;
class Bullet;
class UIPlayerHUD;
class UIPlayerHealth;
#pragma endregion

#pragma region Scripts
class CameraController;
#pragma endregion

#pragma region Debug
class ColliderDebuger;
#pragma endregion

class InGame : public Scene
{
	using Super = Scene;

public:
	InGame(const string& name);
	virtual ~InGame() override = default;

protected:
	virtual void LoadResources() override;
	virtual void CreateRenderProperties() override;
	virtual void CreateSceneContext() override;
};

