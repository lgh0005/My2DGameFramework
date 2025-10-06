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
#include "Engine/UIText.h"
#include "Engine/FlipbookPlayer.h"
#include "Engine/UIButton.h"
#include "Engine/UICanvas.h"
#include "Engine/UICheckBox.h"
#pragma endregion

#pragma region Resources
#include "Engine/RenderPass.h"
#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Font.h"
#include "Engine/Flipbook.h"
#pragma endregion

#pragma region Behaviour
#include "example.h"
#include "example1.h"
#include "example2.h"
#include "example3.h"
#pragma endregion

#pragma region Test Scene
DevScene::DevScene(const string& name) : Super(name)
{

}

void DevScene::CreateSceneContext()
{
#pragma region PREPROCESSING
	RENDER.SetClearColor({ 0.2f, 0.0f, 0.0f, 1.0f });
#pragma endregion

#pragma region REDNER_PASSES
	// Shader : Default texture shader
	{
		_textureShader = make_shared<Shader>
			(
				"TextureShader",
				"../Engine/glsl/default.vert",
				"../Engine/glsl/default.frag"
			);
		_textureShader->Awake();
		_textureShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_textureShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_textureShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_textureShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		RESOURCE.AddResource(static_pointer_cast<IResource>(_textureShader));
	}

	// Shader : Defualt text shader
	{
		_textShader = make_shared<Shader>
			(
				"TextShader",
				"../Engine/glsl/text.vert",
				"../Engine/glsl/text.frag"
			);
		_textShader->Awake();
		_textShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_textShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_textShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_textShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		_textShader->AddUniform(Uniforms::UNIFORM_COLOR);
		RESOURCE.AddResource(static_pointer_cast<IResource>(_textShader));
	}

	// Shader : Default Instancing shader
	{
		_instanceShader = make_shared<Shader>
			(
				"InstanceShader",
				"../Engine/glsl/instance.vert",
				"../Engine/glsl/instance.frag"
			);
		_instanceShader->Awake();
		_instanceShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_instanceShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_instanceShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		_instanceShader->AddUniform(Uniforms::UNIFORM_COLOR);
		RESOURCE.AddResource(static_pointer_cast<IResource>(_instanceShader));
	}

	
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
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_mainCamera->SetTransform(_mainCameraTransform);
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
		_gameObjects.push_back(_uiCamera);
	}

	// UI Render Pass
	_uiRenderPass = make_shared<RenderPass>();
	_uiRenderPass->SetShader(_textShader);
	_uiRenderPass->SetCamera(_uiCameraComponent);

	// texture Render Pass
	_textureRenderPass = make_shared<RenderPass>();
	_textureRenderPass->SetShader(_textureShader);
	_textureRenderPass->SetCamera(_mainCameraComponent);

	// texture Render Pass
	_instanceRenderPass = make_shared<RenderPass>();
	_instanceRenderPass->SetShader(_instanceShader);
	_instanceRenderPass->SetCamera(_mainCameraComponent);
#pragma endregion

#pragma region GAME_OBJECTS
	// Text UI GameObject
	{
		_font = make_shared<Font>("font", "../Resources/Fonts/Crang.ttf", "Hello world!", 64, Colors::White);
		RESOURCE.AddResource(_font);

		auto MyFont = RESOURCE.GetResource<Font>("font");
		auto MyShader = RESOURCE.GetResource<Shader>("TextShader");
		_textTexture = make_shared<UIText>("Text", _uiCameraComponent, MyFont);
		_textTransform = make_shared<Transform>
			(
				"TextTransform",
				glm::vec3(0.0f, 200.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_textObject = make_shared<GameObject>("TextObject");
		_textObject->SetTransform(_textTransform);
		_textObject->AddRenderable(static_pointer_cast<IRenderable>(_textTexture));
		_uiRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_textTexture));
		_gameObjects.push_back(_textObject);
	}

	// Text UI GameObject
	{
		_font2 = make_shared<Font>("font2", "../Resources/Fonts/Crang.ttf", "This is Text!", 64, Colors::Red);
		RESOURCE.AddResource(_font2);

		auto MyFont = RESOURCE.GetResource<Font>("font2");
		auto MyShader = RESOURCE.GetResource<Shader>("TextShader");
		_textTexture2 = make_shared<UIText>("Text2", _uiCameraComponent, MyFont);
		_textTransform2 = make_shared<Transform>
			(
				"TextTransform2",
				glm::vec3(0.0f, -200.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_textObject2 = make_shared<GameObject>("TextObject2");
		_textObject2->SetTransform(_textTransform2);
		_textObject2->AddRenderable(static_pointer_cast<IRenderable>(_textTexture2));
		_uiRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_textTexture2));
		_gameObjects.push_back(_textObject2);
	}

	// Sprite GameObject
	{
		_texture = make_shared<Texture>("Texture", "../Resources/Images/cuphead_idle_0001.png");
		RESOURCE.AddResource(_texture);
		_sprite = make_shared<Sprite>("Sprite", RESOURCE.GetResource<Texture>("Texture"));
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
		_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_sprite));
		_spriteObject->AddBehaviour(static_pointer_cast<IBehaviour>(_sampleScript));
		_gameObjects.push_back(_spriteObject);
	}

	// Flipbook GameObject
	{
		FlipbookInfo info{ 8, 16, 7, 0, 9, 12.0f, true, true };
		_flipbook = make_shared<Flipbook>("Flipbook", "../Resources/Images/cuphead_overworld.png", info);
		RESOURCE.AddResource(_flipbook);
		_flipbookPlayer = make_shared<FlipbookPlayer>("FlipbookPlayer", RESOURCE.GetResource<Flipbook>("Flipbook"));
		_flipbookTransform = make_shared<Transform>
			(
				"FlipbookTransform",
				glm::vec3(100.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_flipbookObject = make_shared<GameObject>("FlipbookObject");
		_flipbookObject->SetTransform(_flipbookTransform);
		_flipbookObject->AddRenderable(static_pointer_cast<IRenderable>(_flipbookPlayer));
		_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_flipbookPlayer));
		_flipbookObject->SetParent(_spriteObject);
		_gameObjects.push_back(_flipbookObject);
	}

	// Button UI GameObject
	{
		_buttonHoveredTexture = make_shared<Texture>("HOVERED", "../Resources/Images/b_1_hover.png");
		RESOURCE.AddResource(_buttonHoveredTexture);
		_buttonHoveredTexture->Awake();

		_buttonTexture = make_shared<Texture>("buttonTexture", "../Resources/Images/b_1.png");
		RESOURCE.AddResource(_buttonTexture);
		auto ButtonTexture = RESOURCE.GetResource<ITexture>("buttonTexture");
		_button = make_shared<UIButton>
			(
				"Button",
				_uiCameraComponent,
				ButtonTexture,
				glm::vec2(201.0f, 93.0f),
				Inputs::Mouse::Left
			);

		_uiButtonTransform = make_shared<Transform>
			(
				"ButtonTransform",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_sampleScript2 = make_shared<example2>("example2");
		_uiButtonObject = make_shared<GameObject>("ButtonObject");
		_uiButtonObject->SetTransform(_uiButtonTransform);
		_uiButtonObject->AddRenderable(static_pointer_cast<IRenderable>(_button));
		_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_button));
		_uiButtonObject->AddBehaviour(static_pointer_cast<IBehaviour>(_sampleScript2));
		_gameObjects.push_back(_uiButtonObject);
	}

	// Button CheckBox UI
	{
		_chechboxClicked = make_shared<Texture>("CLICKED", "../Resources/Images/b_2_click.png");
		RESOURCE.AddResource(_chechboxClicked);
		_chechboxClicked->Awake();

		_checkboxTexture = make_shared<Texture>("CheckBoxTexture", "../Resources/Images/b_2.png");
		RESOURCE.AddResource(_checkboxTexture);
		auto CheckBoxTexture = RESOURCE.GetResource<ITexture>("CheckBoxTexture");
		_checkbox = make_shared<UICheckBox>
			(
				"CheckBox",
				_uiCameraComponent,
				CheckBoxTexture,
				glm::vec2(205.0f, 205.0f),
				Inputs::Mouse::Left
			);

		_uiCheckBoxTransform = make_shared<Transform>
			(
				"CheckBoxTransform",
				glm::vec3(300.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.25f, 0.25f, 1.0f)
			);
		_sampleScript3 = make_shared<example3>("example3");
		_uiCheckBoxObject = make_shared<GameObject>("CheckBoxObject");
		_uiCheckBoxObject->SetTransform(_uiCheckBoxTransform);
		_uiCheckBoxObject->AddRenderable(static_pointer_cast<IRenderable>(_checkbox));
		_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_checkbox));
		_uiCheckBoxObject->AddBehaviour(static_pointer_cast<IBehaviour>(_sampleScript3));
		_gameObjects.push_back(_uiCheckBoxObject);
	}

	// UI Canvas GameObject
	{
		_uiCanvas = make_shared<UICanvas>("MyCanvas", _uiCameraComponent, glm::vec2(300.0f, 200.0f));
		_uiCanvasTransform = make_shared<Transform>
			(
				"ButtonTransform",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_uiCanvasObject = make_shared<GameObject>("CanvasObject");
		_uiCanvasObject->SetTransform(_uiCanvasTransform);
		_uiCanvasObject->AddComponent(_uiCanvas);
		_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_button));
		_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_textTexture));
		_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_textTexture2));
		_uiCanvas->AddUIComponent(static_pointer_cast<IUIElement>(_checkbox));
		_gameObjects.push_back(_uiCanvasObject);
	}

	RENDER.AddRenderPass(_uiRenderPass);
	RENDER.AddRenderPass(_textureRenderPass);
	RENDER.AddRenderPass(_instanceRenderPass);

	
#pragma endregion

	
}
#pragma endregion