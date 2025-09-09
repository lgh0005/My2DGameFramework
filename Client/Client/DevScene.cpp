#include "pch.h"
#include "DevScene.h"

#pragma region GameObject
#include "Engine/GameObject.h"
#pragma endregion

#pragma region Components
#include "Engine/IRenderable.h"
#include "Engine/Transform.h"
#include "Engine/Camera.h"
#include "Engine/Sprite.h"
#include "Engine/Text.h"
#include "Engine/FlipbookPlayer.h"
#pragma endregion

#pragma region Resources
#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Font.h"
#include "Engine/Flipbook.h"
#pragma endregion

#pragma region Behaviour
#include "example.h"
#pragma endregion

#pragma region Test Scene
DevScene::DevScene(const string& name) : Super(name)
{

}

void DevScene::CreateSceneContext()
{
	/*==================
	*   preprocessing  *
	===================*/
	RENDER.SetClearColor({ 0.2f, 0.0f, 0.0f, 1.0f });

	// Main Camera
	{
		_mainCameraComponent = make_shared<Camera>("MainCameraComponent");
		_mainCamera = make_shared<GameObject>("MainCamera");
		_mainCamera->AddComponent(_mainCameraComponent);
		_mainCameraTransform = make_shared<Transform>
		(
			"MainCameraTransform",
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f ,1.0f, 1.0f)
		);
		_mainCamera->SetTransform(_mainCameraTransform);
		RENDER.AddCamera(Render::RenderLayer::World, _mainCameraComponent);
		_gameObjects.push_back(_mainCamera);
	}

	// UI Camera
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
		RENDER.AddCamera(Render::RenderLayer::UI, _uiCameraComponent);
		_gameObjects.push_back(_uiCamera);
	}

	// Shader : Default texture shader
	{
		_textureShader = make_shared<Shader>
		(
			"TextureShader",
			"../Engine/glsl/default.vert",
			"../Engine/glsl/default.frag",
			vector<const char*>
			{
				Uniforms::UNIFORM_MODEL,
				Uniforms::UNIFORM_VIEW,
				Uniforms::UNIFORM_PROJECTION,
				Uniforms::UNIFORM_TEXTURE
			}
		);
		RESOURCE.AddResource(_textureShader);
	}

	// Shader : Defualt text shader
	{
		_textShader = make_shared<Shader>
		(
			"TextShader",
			"../Engine/glsl/text.vert",
			"../Engine/glsl/text.frag",
			vector<const char*>
			{
				Uniforms::UNIFORM_MODEL,
				Uniforms::UNIFORM_VIEW,
				Uniforms::UNIFORM_PROJECTION,
				Uniforms::UNIFORM_TEXTURE,
				Uniforms::UNIFORM_COLOR
			}
		);
		RESOURCE.AddResource(_textShader);
	}

	// Text UI GameObject
	{
		_font = make_shared<Font>("font", "../Resources/Fonts/Crang.ttf", "Hello world!", 64, Colors::White);
		RESOURCE.AddResource(_font);
		_textTexture = make_shared<Text>("Text", RESOURCE.GetResource<Font>("font"), RESOURCE.GetResource<Shader>("TextShader"));
		RENDER.AddRenderable(Render::RenderLayer::UI, _textTexture);
		_textTransform = make_shared<Transform>
		(
			"TextTransform",
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		_textObject = make_shared<GameObject>("TextObject");
		_textObject->SetTransform(_textTransform);
		_textObject->AddRenderable(static_pointer_cast<IRenderable>(_textTexture));
		_gameObjects.push_back(_textObject);
	}

	// Sprite GameObject
	{
		_texture = make_shared<Texture>("Texture", "../Resources/Images/cuphead_idle_0001.png");
		RESOURCE.AddResource(_texture);
		_sprite = make_shared<Sprite>("Sprite", RESOURCE.GetResource<Texture>("Texture"), RESOURCE.GetResource<Shader>("TextureShader"));
		RENDER.AddRenderable(Render::RenderLayer::World, _sprite);
		_spriteTransform = make_shared<Transform>
		(
			"TextTransform",
			glm::vec3(300.0f, 200.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		_sampleScript = make_shared<example>("example");
		_spriteObject = make_shared<GameObject>("SpriteObject");
		_spriteObject->SetTransform(_spriteTransform);
		_spriteObject->AddRenderable(static_pointer_cast<IRenderable>(_sprite));
		_spriteObject->AddBehaviour(static_pointer_cast<IBehaviour>(_sampleScript));
		_gameObjects.push_back(_spriteObject);
	}

	// Flipbook GameObject
	{
		FlipbookInfo info{ 8, 16, 0, 0, 3, 12.0f, true, true };
		_flipbook = make_shared<Flipbook>("Flipbook", "../Resources/Images/cuphead_overworld.png", info);
		RESOURCE.AddResource(_flipbook);
		_flipbookPlayer = make_shared<FlipbookPlayer>("FlipbookPlayer", RESOURCE.GetResource<Flipbook>("Flipbook"), RESOURCE.GetResource<Shader>("TextureShader"));
		RENDER.AddRenderable(Render::RenderLayer::World, _flipbookPlayer);
		_spriteTransform = make_shared<Transform>
		(
			"FlipbookTransform",
			glm::vec3(-300.0f, 200.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		_flipbookObject = make_shared<GameObject>("FlipbookObject");
		_flipbookObject->SetTransform(_spriteTransform);
		_flipbookObject->AddRenderable(static_pointer_cast<IRenderable>(_flipbookPlayer));
		_gameObjects.push_back(_flipbookObject);
	}
}
#pragma endregion