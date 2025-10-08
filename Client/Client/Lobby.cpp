#include "pch.h"
#include "Lobby.h"

#pragma region Prefabs
#include "Ground.h"
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
	}
}

void Lobby::LoadResources()
{
	// Load textures
	_groundTexture = make_shared<Texture>("Ground", "../Resources/Images/Extras/groundBig.png");
	RESOURCE.AddResource(_groundTexture);
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

	// PREFAB_TEST
	_ground = make_shared<Ground>();
	_ground->SetRenderPass(_textureRenderPass);

	auto obj1 = _ground->Instantiate("Ground1", { -384.0f, -300.0f, 0.f });
	_gameObjects.push_back(obj1);

	auto obj2 = _ground->Instantiate("Ground2", { 384.0f, -300.0f, 0.f });
	_gameObjects.push_back(obj2);


#pragma endregion

#pragma region PRESENT_RENDER_PASSES
	// RENDER.AddRenderPass(_uiRenderPass);
	RENDER.AddRenderPass(_textureRenderPass);
}

