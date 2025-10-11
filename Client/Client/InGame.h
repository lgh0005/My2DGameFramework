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
#pragma endregion

#pragma region NECESSARY_RESOURCES
private:
	void CreateRenderProperties();
#pragma endregion
};

