#include "pch.h"
#include "UIPlayerHUD.h"

shared_ptr<GameObject> UIPlayerHUD::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	// GameObject List
	shared_ptr<Scene> currentScene;
	if (Utils::IsValidPtr(_currentScene, currentScene) == false) return nullptr;
	auto& GameObjectList = currentScene->GetGameObjectList();

	// UI Camera
	shared_ptr<Camera> camera = _renderPass->GetCamera();

	// Score
	{
		_scoreTextGameObject = make_shared<GameObject>("ScoreText");
		_scoreTextTransform = make_shared<Transform>
			(
				"TitleText1",
				glm::vec3(150.0f, 360.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_scoreText = make_shared<UIText>("Score", camera, RESOURCE.GetResource<Font>("Score"));
		_scoreTextGameObject->SetTransform(_scoreTextTransform);
		_scoreTextGameObject->AddRenderable(_scoreText);
		_renderPass->AddRenderable(_scoreText);
		GameObjectList.push_back(_scoreTextGameObject);
	}

	// Score number
	{
		for (int i = 0; i < 6; i++)
		{
			string objName = "ScoreNumText_" + to_string(i);
			auto numGameObject = make_shared<GameObject>(objName);

			auto numTransform = make_shared<Transform>
			(
				"ScoreNumTransform_" + to_string(i),
				glm::vec3(300.0f + i * 50.0f, 360.0f, 0.0f),
				glm::vec3(0.0f),
				glm::vec3(1.0f)
			);

			auto numText = make_shared<UIText>
			(
				"0", // �ʱⰪ
				camera,
				RESOURCE.GetResource<Font>("0")
			);

			numGameObject->SetTransform(numTransform);
			numGameObject->AddRenderable(numText);
			_renderPass->AddRenderable(numText);
			GameObjectList.push_back(numGameObject);

			_scoreNumTextObjects.push_back(numGameObject);
			_scoreNumText.push_back(numText);
			_scoreNumtextTransform.push_back(numTransform);
		}
	}

	// No weapon Text
	{
		_noWeaponTextGameObject = make_shared<GameObject>("NoWeapon");
		_noWeaponTextGameTransform = make_shared<Transform>
			(
				"NoWeaponText",
				glm::vec3(380.0f, -320.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_noWeaponText = make_shared<UIText>("Normal", camera, RESOURCE.GetResource<Font>("Normal"));
		_noWeaponTextGameObject->SetTransform(_noWeaponTextGameTransform);
		_noWeaponTextGameObject->AddRenderable(_noWeaponText);
		_renderPass->AddRenderable(_noWeaponText);
		_noWeaponTextGameObject->SetActive(true);
		GameObjectList.push_back(_noWeaponTextGameObject);
	}

	// Pistol text
	{
		_pistolTextGameObject = make_shared<GameObject>("PistolText");
		_pistolTextGameTransform = make_shared<Transform>
			(
				"PistolText",
				glm::vec3(380.0f, -320.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_pistolText = make_shared<UIText>("Pistol", camera, RESOURCE.GetResource<Font>("Pistol"));
		_pistolTextGameObject->SetTransform(_pistolTextGameTransform);
		_pistolTextGameObject->AddRenderable(_pistolText);
		_renderPass->AddRenderable(_pistolText);
		_pistolTextGameObject->SetActive(false);
		GameObjectList.push_back(_pistolTextGameObject);
	}

	// Sword text
	{
		_swordTextGameObject = make_shared<GameObject>("SwordText");
		_swordGameTransform = make_shared<Transform>
			(
				"SwordText",
				glm::vec3(380.0f, -320.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_swordText = make_shared<UIText>("Sword", camera, RESOURCE.GetResource<Font>("Sword"));
		_swordTextGameObject->SetTransform(_swordGameTransform);
		_swordTextGameObject->AddRenderable(_swordText);
		_renderPass->AddRenderable(_swordText);
		_swordTextGameObject->SetActive(false);
		GameObjectList.push_back(_swordTextGameObject);
	}

	// Canvas
	{
		_mainHUDCanvas = make_shared<GameObject>("MainHUD");
		_uiCanvas = make_shared<UICanvas>("MainHUDCanavs", camera, glm::vec2(WindowConfig::GWinSizeX, WindowConfig::GWinSizeY));
		_uiCanvasTransform = make_shared<Transform>
			(
				"MainHUDUICanvas",
				position, rotation, scale
			);
		_mainHUDCanvas->SetTransform(_uiCanvasTransform);

		_uiCanvas->AddUIComponent(_scoreText);
		_uiCanvas->AddUIComponent(_noWeaponText);
		_uiCanvas->AddUIComponent(_pistolText);
		_uiCanvas->AddUIComponent(_swordText);
		for (auto& numText : _scoreNumText) _uiCanvas->AddUIComponent(numText);
		_mainHUDCanvas->AddComponent(_uiCanvas);
	}

	return _mainHUDCanvas;
}
