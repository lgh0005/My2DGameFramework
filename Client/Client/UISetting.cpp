#include "pch.h"
#include "UISetting.h"

#pragma region Scripts
#include "CloseButtonScript.h"
#include "BGMCheckBoxScript.h"
#include "SFXCheckBoxScript.h"
#pragma endregion

UISetting::UISetting(const string& name) : Super(name)
{

}

shared_ptr<GameObject> UISetting::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;
	auto& GameObjectList = scene->GetGameObjectList();

	shared_ptr<GameObject> uiCameraObj = scene->GetGameObject("UICamera");
	shared_ptr<Camera> uiCamera = static_pointer_cast<Camera>(uiCameraObj->GetComponent("UICameraComponent"));

	// Canvas Panel
	{
		_settingUIPanelGameObject = make_shared<GameObject>("SettingUIPanel");
		_settingUIPanelTransform = make_shared<Transform>
		(
			"SettingPanel",
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		_settingUIPanel = make_shared<UIImage>("SettingUIPanel", uiCamera, RESOURCE.GetResource<Texture>("UIPanel"));
		_settingUIPanelGameObject->SetTransform(_settingUIPanelTransform);
		_settingUIPanelGameObject->AddRenderable(_settingUIPanel);
		scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_settingUIPanel);
		_settingUIPanelGameObject->SetActive(false);
		GameObjectList.push_back(_settingUIPanelGameObject);
	}

	// Setting Text #1
	{
		_settingUITextGameObject1 = make_shared<GameObject>("SettingUIText1");
		_settingUITextTransform1 = make_shared<Transform>
		(
			"TitleText1",
			glm::vec3(-150.0f, 100.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		_settingUIText1 = make_shared<UIText>("SettingUIText1", uiCamera, RESOURCE.GetResource<Font>("bgm"));
		_settingUITextGameObject1->SetTransform(_settingUITextTransform1);
		_settingUITextGameObject1->AddRenderable(_settingUIText1);
		scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_settingUIText1);
		_settingUITextGameObject1->SetActive(false);
		GameObjectList.push_back(_settingUITextGameObject1);
	}

	// Setting Text #2
	{
		_settingUITextGameObject2 = make_shared<GameObject>("SettingUIText2");
		_settingUITextTransform2 = make_shared<Transform>
			(
				"TitleText1",
				glm::vec3(-150.0f, -100.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_settingUIText2 = make_shared<UIText>("SettingUIText2", uiCamera, RESOURCE.GetResource<Font>("sfx"));
		_settingUITextGameObject2->SetTransform(_settingUITextTransform2);
		_settingUITextGameObject2->AddRenderable(_settingUIText2);
		scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_settingUIText2);
		_settingUITextGameObject2->SetActive(false);
		GameObjectList.push_back(_settingUITextGameObject2);
	}
	
	// Toggles
	{
		_settingUIToggleTexture = RESOURCE.GetResource<Texture>("UIToggle");

		// Toggle #1
		{
			_settingUIToggleGameObject1 = make_shared<GameObject>("bgmToggle");
			_settingUIToggleTransform1 = make_shared<Transform>
			(
				"Toggle1",
				glm::vec3(150.0f, 100.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
			_settingUICheckBox1 = make_shared<UICheckBox>("bgmToggle", uiCamera, _settingUIToggleTexture, glm::vec2(100.f, 100.f), Inputs::Mouse::Left);
			_settingUIToggleGameObject1->SetTransform(_settingUIToggleTransform1);
			_settingUIToggleGameObject1->AddRenderable(_settingUICheckBox1);
			scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_settingUICheckBox1);
			auto _bgmToggleScript = make_shared<BGMCheckBoxScript>("bgmToggleScript");
			_bgmToggleScript->SetCurrentScene(scene);
			_settingUIToggleGameObject1->AddBehaviour(_bgmToggleScript);
			_settingUIToggleGameObject1->SetActive(false);
			GameObjectList.push_back(_settingUIToggleGameObject1);
		}

		// Toggle #2
		{
			_settingUIToggleGameObject2 = make_shared<GameObject>("sfxToggle");
			_settingUIToggleTransform2 = make_shared<Transform>
				(
					"Toggle1",
					glm::vec3(150.0f, -100.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_settingUICheckBox2 = make_shared<UICheckBox>("sfxToggle", uiCamera, _settingUIToggleTexture, glm::vec2(100.f, 100.f), Inputs::Mouse::Left);
			_settingUIToggleGameObject2->SetTransform(_settingUIToggleTransform2);
			_settingUIToggleGameObject2->AddRenderable(_settingUICheckBox2);
			scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_settingUICheckBox2);
			auto _sfxToggleScript = make_shared<SFXCheckBoxScript>("sfxToggleScript");
			_sfxToggleScript->SetCurrentScene(scene);
			_settingUIToggleGameObject2->AddBehaviour(_sfxToggleScript);
			_settingUIToggleGameObject2->SetActive(false);
			GameObjectList.push_back(_settingUIToggleGameObject2);
		}

		// Icon #1
		{
			_closeIconGameObject1 = make_shared<GameObject>("Check1");
			_closeIconTransform1 = make_shared<Transform>
			(
				"checkIcon1",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
			_closeIcon1 = make_shared<UIImage>("check", uiCamera, RESOURCE.GetResource<Texture>("UICheck"));
			_closeIconGameObject1->SetTransform(_closeIconTransform1);
			_closeIconGameObject1->AddRenderable(_closeIcon1);
			scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_closeIcon1);
			_closeIconGameObject1->SetParent(_settingUIToggleGameObject1);
			_closeIconGameObject1->SetActive(false);
			GameObjectList.push_back(_closeIconGameObject1);
		}

		// Icon #2
		{
			_closeIconGameObject2 = make_shared<GameObject>("Check2");
			_closeIconTransform2 = make_shared<Transform>
				(
					"checkIcon2",
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				);
			_closeIcon2 = make_shared<UIImage>("check", uiCamera, RESOURCE.GetResource<Texture>("UICheck"));
			_closeIconGameObject2->SetTransform(_closeIconTransform2);
			_closeIconGameObject2->AddRenderable(_closeIcon2);
			scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_closeIcon2);
			_closeIconGameObject2->SetParent(_settingUIToggleGameObject2);
			_closeIconGameObject2->SetActive(false);
			GameObjectList.push_back(_closeIconGameObject2);
		}
	}

	// Button
	{
		_settingUICloseGameObject = make_shared<GameObject>("SettingClose");
		_settingUICloseTransform = make_shared<Transform>
			(
				"CloseButton",
				glm::vec3(380.0f, 220.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_settingUICloseButton = make_shared<UIButton>("CloseButton", uiCamera, _settingUIToggleTexture, glm::vec2(100.f, 100.f), Inputs::Mouse::Left);
		_settingUICloseGameObject->SetTransform(_settingUICloseTransform);
		_settingUICloseGameObject->AddRenderable(_settingUICloseButton);
		scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_settingUICloseButton);
		auto _settingUICloseScript = make_shared<CloseButtonScript>("CloseButtonScript");
		_settingUICloseScript->SetCurrentScene(scene);
		_settingUICloseGameObject->AddBehaviour(_settingUICloseScript);
		_settingUICloseGameObject->SetActive(false);
		GameObjectList.push_back(_settingUICloseGameObject);
	}

	// Icon #3
	{
		_closeIconGameObject3 = make_shared<GameObject>("Close");
		_closeIconTransform3 = make_shared<Transform>
			(
				"checkIcon2",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_closeIcon3 = make_shared<UIImage>("close", uiCamera, RESOURCE.GetResource<Texture>("UIBack"));
		_closeIconGameObject3->SetTransform(_closeIconTransform3);
		_closeIconGameObject3->AddRenderable(_closeIcon3);
		scene->GetRenderPass("_SettingUIRenderPass")->AddRenderable(_closeIcon3);
		_closeIconGameObject3->SetParent(_settingUICloseGameObject);
		_closeIconGameObject3->SetActive(false);
		GameObjectList.push_back(_closeIconGameObject3);
	}

	// Canvas
	{
		_settingUIGameObject = make_shared<GameObject>("SettingUI");
		_uiCanvas = make_shared<UICanvas>("SettingUICanvas", uiCamera, glm::vec2(300.0f, 200.0f));
		_uiCanvasTransform = make_shared<Transform>
			(
				"SettingUICanvas",
				position, rotation, scale
			);
		_settingUIGameObject->SetTransform(_uiCanvasTransform);

		_uiCanvas->AddUIComponent(_settingUIPanel);
		_uiCanvas->AddUIComponent(_settingUIText1);
		_uiCanvas->AddUIComponent(_settingUIText2);
		_uiCanvas->AddUIComponent(_settingUICheckBox1);
		_uiCanvas->AddUIComponent(_settingUICheckBox2);
		_uiCanvas->AddUIComponent(_settingUICloseButton);

		_settingUIGameObject->SetActive(false);
		_settingUIGameObject->AddComponent(_uiCanvas);
	}

	return _settingUIGameObject;
}
