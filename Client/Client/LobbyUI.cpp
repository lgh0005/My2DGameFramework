#include "pch.h"
#include "LobbyUI.h"

#pragma region Scripts
#include "UIBlocker.h"
#include "StartButtonScript.h"
#include "OptionButtonScript.h"
#include "QuitButtonScript.h"
#pragma endregion

LobbyUI::LobbyUI(const string& name) : Super(name)
{

}

shared_ptr<GameObject> LobbyUI::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;
	auto& GameObjectList = scene->GetGameObjectList();

	shared_ptr<GameObject> uiCameraObj = scene->GetGameObject("UICamera");
	shared_ptr<Camera> uiCamera = static_pointer_cast<Camera>(uiCameraObj->GetComponent("UICameraComponent"));

	shared_ptr<GameObject> mainCameraObj = scene->GetGameObject("MainCamera");
	shared_ptr<Camera> mainCamera = static_pointer_cast<Camera>(mainCameraObj->GetComponent("MainCameraComponent"));
	 
	// UI Blocker
	{
		_uiBlocker = make_shared<GameObject>("UIBlocker");
		_uiBlockerTransform = make_shared<Transform>
			(
				"DummyTransform",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_uiBlocker->SetTransform(_uiBlockerTransform);
		_uiBlockerScript = make_shared<UIBlocker>("UIBlocker");
		_uiBlockerScript->SetCurrentScene(scene);
		_uiBlocker->AddBehaviour(_uiBlockerScript);
		GameObjectList.push_back(_uiBlocker);
	}

	// Title Text #1
	{
		_title1Text = make_shared<UIText>("Title1", uiCamera, RESOURCE.GetResource<Font>("Title1"));
		_title1Transform = make_shared<Transform>
			(
				"Title1_Transform",
				glm::vec3(0.0f, 320.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_title1 = make_shared<GameObject>("Title1");
		_title1->SetTransform(_title1Transform);
		_title1->AddRenderable(static_pointer_cast<IRenderable>(_title1Text));
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_title1Text);
		GameObjectList.push_back(_title1);
	}

	// Title Text #2
	{
		_title2Text = make_shared<UIText>("Title2", uiCamera, RESOURCE.GetResource<Font>("Title2"));
		_title2Transform = make_shared<Transform>
			(
				"Title2_Transform",
				glm::vec3(0.0f, 220.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_title2 = make_shared<GameObject>("Title2");
		_title2->SetTransform(_title2Transform);
		_title2->AddRenderable(static_pointer_cast<IRenderable>(_title2Text));
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_title2Text);
		GameObjectList.push_back(_title2);
	}

	// Button #1
	{
		_button1Text = make_shared<UIText>("Start", uiCamera, RESOURCE.GetResource<Font>("Start"));
		_button1Button = make_shared<UIButton>
			(
				"StartButton",
				uiCamera,
				RESOURCE.GetResource<Texture>("Button_Normal"),
				glm::vec2(260.0f, 81.0f),
				Inputs::Mouse::Left
			);

		_button1Transform = make_shared<Transform>
			(
				"StartButton_Transform",
				glm::vec3(0.0f, 60.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_button1 = make_shared<GameObject>("StartButton");
		_button1->SetTransform(_button1Transform);
		_button1->AddRenderable(static_pointer_cast<IRenderable>(_button1Text));
		_button1->AddRenderable(static_pointer_cast<IRenderable>(_button1Button));
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_button1Text);
		scene->GetRenderPass("_textureRenderPass")->AddRenderable(_button1Button);
		_button1Script = make_shared<StartButtonScript>("StartButtonScript");
		_button1Script->SetCurrentScene(scene);
		_button1->AddBehaviour(_button1Script);
		GameObjectList.push_back(_button1);
	}

	// Button #2
	{
		_button2Text = make_shared<UIText>("Option", uiCamera, RESOURCE.GetResource<Font>("Option"));
		_button2Button = make_shared<UIButton>
			(
				"OptionButton",
				uiCamera,
				RESOURCE.GetResource<Texture>("Button_Normal"),
				glm::vec2(260.0f, 81.0f),
				Inputs::Mouse::Left
			);

		_button2Transform = make_shared<Transform>
			(
				"ButtonTransform",
				glm::vec3(0.0f, -40.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_button2 = make_shared<GameObject>("ButtonObject2");
		_button2->SetTransform(_button2Transform);
		_button2->AddRenderable(static_pointer_cast<IRenderable>(_button2Text));
		_button2->AddRenderable(static_pointer_cast<IRenderable>(_button2Button));
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_button2Text);
		scene->GetRenderPass("_textureRenderPass")->AddRenderable(_button2Button);
		_button2Script = make_shared<OptionButtonScript>("OptionButtonScript");
		_button2Script->SetCurrentScene(scene);
		_button2->AddBehaviour(_button2Script);
		GameObjectList.push_back(_button2);
	}

	// Button #3
	{
		_button3Text = make_shared<UIText>("Quit", uiCamera, RESOURCE.GetResource<Font>("Quit"));
		_button3Button = make_shared<UIButton>
			(
				"QuitButton",
				uiCamera,
				RESOURCE.GetResource<Texture>("Button_Normal"),
				glm::vec2(260.0f, 81.0f),
				Inputs::Mouse::Left
			);

		_button3Transform = make_shared<Transform>
			(
				"ButtonTransform_Transform",
				glm::vec3(0.0f, -140.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_button3 = make_shared<GameObject>("ButtonObject3");
		_button3->SetTransform(_button3Transform);
		_button3->AddRenderable(static_pointer_cast<IRenderable>(_button3Text));
		_button3->AddRenderable(static_pointer_cast<IRenderable>(_button3Button));
		scene->GetRenderPass("_textRenderPass")->AddRenderable(_button3Text);
		scene->GetRenderPass("_textureRenderPass")->AddRenderable(_button3Button);
		_button3Script = make_shared<QuitButtonScript>("QuitButtonScript");
		_button3Script->SetCurrentScene(scene);
		_button3->AddBehaviour(_button3Script);
		GameObjectList.push_back(_button3);
	}

	// Canvas
	{
		_mainUIComponent = make_shared<UICanvas>("MainUICanvas", uiCamera, glm::vec2(300.0f, 200.0f));
		_mainUITransform = make_shared<Transform>
			(
				"MainUICanvas",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		_mainUI = make_shared<GameObject>("MainUICanvas");
		_mainUI->SetTransform(_mainUITransform);
		_mainUI->AddComponent(_mainUIComponent);
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_button1Button));
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_button2Button));
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_button3Button));
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_title1Text));
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_title2Text));
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_button1Text));
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_button2Text));
		_mainUIComponent->AddUIComponent(static_pointer_cast<IUIElement>(_button3Text));
	}

	return _mainUI;
}
