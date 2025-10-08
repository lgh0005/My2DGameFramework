#include "pch.h"
#include "TestScene.h"

TestScene::TestScene(const string& name) : Super(name)
{

}

void TestScene::CreateSceneContext()
{
#pragma region PREPROCESSING
	RENDER.SetClearColor({ 0.f, 0.0f, 0.2f, 1.0f });
#pragma endregion

	// Shader : Default texture shader
	{
		_textureShader = make_shared<Shader>
			(
				"TextureShader",
				"../Engine/glsl/default.vert",
				"../Engine/glsl/default.frag"
			);
		_textureShader->Init();
		_textureShader->AddUniform(Uniforms::UNIFORM_MODEL);
		_textureShader->AddUniform(Uniforms::UNIFORM_VIEW);
		_textureShader->AddUniform(Uniforms::UNIFORM_PROJECTION);
		_textureShader->AddUniform(Uniforms::UNIFORM_TEXTURE);
		RESOURCE.AddResource(static_pointer_cast<IResource>(_textureShader));
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

	// texture Render Pass
	_textureRenderPass = make_shared<RenderPass>();
	_textureRenderPass->SetShader(_textureShader);
	_textureRenderPass->SetCamera(_mainCameraComponent);


	// Sprite GameObject
	{
		_texture = make_shared<Texture>("Texture", "../Resources/Images/cuphead_idle_0001.png");
		RESOURCE.AddResource(_texture);
		_sprite = make_shared<Sprite>("Sprite", RESOURCE.GetResource<Texture>("Texture"));
		_spriteTransform = make_shared<Transform>
			(
				"TextTransform",
				glm::vec3(-300.0f, 200.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_spriteObject = make_shared<GameObject>("SpriteObject");
		_spriteObject->SetTransform(_spriteTransform);
		_spriteObject->AddRenderable(static_pointer_cast<IRenderable>(_sprite));
		_textureRenderPass->AddRenderable(static_pointer_cast<IRenderable>(_sprite));
		_gameObjects.push_back(_spriteObject);
	}

	RENDER.AddRenderPass(_textureRenderPass);

#pragma region AUDIO_TEST_BGM
	shared_ptr<BGM> MyBGM = make_shared<BGM>
		(
			"DadnMe",
			"../Resources/Audio/BGM/power_up.mp3",
			FMOD_LOOP_NORMAL
		);
	RESOURCE.AddResource(MyBGM);
	AUDIO.AddBGM(MyBGM);
	AUDIO.PlayBGM("DadnMe");
#pragma endregion
}
