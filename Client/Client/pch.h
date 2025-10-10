#pragma once

// Framework
#include "Engine/EnginePch.h"
#ifdef _DEBUG
#pragma comment(lib, "Engine/Debug/Engine.lib")
#else
#pragma comment(lib, "Engine/Release/Engine.lib")
#endif

#include "Engine/Game.h"
#include "Engine/Scene.h"

// Launcher
#include "Launcher.h"

// Game build essestials
#pragma region GameObject
#include "Engine/GameObject.h"
#pragma endregion

#pragma region Components
#include "Engine/IRenderable.h"
#include "Engine/Transform.h"
#include "Engine/Camera.h"
#include "Engine/Sprite.h"
#include "Engine/UIText.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/UIButton.h"
#include "Engine/UICanvas.h"
#include "Engine/UICheckBox.h"
#include "Engine/BoxCollider.h"
#pragma endregion

#pragma region Resources
#include "Engine/RenderPass.h"
#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Font.h"
#include "Engine/Flipbook.h"
#include "Engine/BGM.h"
#include "Engine/SFX.h"
#pragma endregion