#include "pch.h"
#include "UIPlayerHUD.h"
#include "UIPlayerHealth.h"

UIPlayerHUD::UIPlayerHUD(const string& name) : Super(name)
{

}

shared_ptr<GameObject> UIPlayerHUD::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;
	auto& GameObjectList = scene->GetGameObjectList();

	shared_ptr<GameObject> uiCameraObj = scene->GetGameObject("UICamera");
	shared_ptr<Camera> uiCamera = static_pointer_cast<Camera>(uiCameraObj->GetComponent("UICameraComponent"));

	// Score
	{
		_scoreTextGameObject = make_shared<GameObject>("ScoreText");
		_scoreTextTransform = make_shared<Transform>
			(
				"TitleText1",
				glm::vec3(200.0f, 360.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_scoreText = make_shared<UIText>("Score", uiCamera, RESOURCE.GetResource<Font>("Score"));
		_scoreTextGameObject->SetTransform(_scoreTextTransform);
		_scoreTextGameObject->AddRenderable(_scoreText);
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_scoreText);
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
				glm::vec3(350.0f + i * 40.0f, 360.0f, 0.0f),
				glm::vec3(0.0f),
				glm::vec3(1.0f)
			);

			auto numText = make_shared<UIText>
			(
				"0",
				uiCamera,
				RESOURCE.GetResource<Font>("0")
			);

			numGameObject->SetTransform(numTransform);
			numGameObject->AddRenderable(numText);
			scene->GetRenderPass("_textRenderPass")->AddRenderable(numText);
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
		_noWeaponText = make_shared<UIText>("Normal", uiCamera, RESOURCE.GetResource<Font>("Normal"));
		_noWeaponTextGameObject->SetTransform(_noWeaponTextGameTransform);
		_noWeaponTextGameObject->AddRenderable(_noWeaponText);
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_noWeaponText);
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
		_pistolText = make_shared<UIText>("Pistol", uiCamera, RESOURCE.GetResource<Font>("Pistol"));
		_pistolTextGameObject->SetTransform(_pistolTextGameTransform);
		_pistolTextGameObject->AddRenderable(_pistolText);
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_pistolText);
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
		_swordText = make_shared<UIText>("Sword", uiCamera, RESOURCE.GetResource<Font>("Sword"));
		_swordTextGameObject->SetTransform(_swordGameTransform);
		_swordTextGameObject->AddRenderable(_swordText);
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_swordText);
		_swordTextGameObject->SetActive(false);
		GameObjectList.push_back(_swordTextGameObject);
	}

	// Health Icon
	shared_ptr<UIPlayerHealth> _playerHealth = make_shared<UIPlayerHealth>("PlayerHealth");
	_playerHealth->SetCurrentScene(scene);
	auto icon1 = _playerHealth->Instantiate("health1", { -550.0f, 350.0f, 0.0f });
	GameObjectList.push_back(icon1);
	auto icon2 = _playerHealth->Instantiate("health2", { -480.0f, 350.0f, 0.0f });
	GameObjectList.push_back(icon2);
	auto icon3 = _playerHealth->Instantiate("health3", { -410.0f, 350.0f, 0.0f });
	GameObjectList.push_back(icon3);

	// Canvas
	{
		_mainHUDCanvas = make_shared<GameObject>("MainHUD");
		_uiCanvas = make_shared<UICanvas>("MainHUDCanavs", uiCamera, glm::vec2(WindowConfig::GWinSizeX, WindowConfig::GWinSizeY));
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
