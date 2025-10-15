#pragma once
#include "Engine\Prefab.h"

class UISetting : public Prefab
{
	using Super = Prefab;

public:
	UISetting(const string& name);
	virtual ~UISetting() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;

private:

	// Panel Image
	shared_ptr<GameObject> _settingUIPanelGameObject;
	shared_ptr<UIImage> _settingUIPanel;
	shared_ptr<Transform> _settingUIPanelTransform;

	// Text #1
	shared_ptr<GameObject> _settingUITextGameObject1;
	shared_ptr<UIText> _settingUIText1;
	shared_ptr<Transform> _settingUITextTransform1;

	// Text #2
	shared_ptr<GameObject> _settingUITextGameObject2;
	shared_ptr<UIText> _settingUIText2;
	shared_ptr<Transform> _settingUITextTransform2;

#pragma region Toggle

	// Toggle Texture
	shared_ptr<Texture> _settingUIToggleTexture;

	// Toggle #1
	shared_ptr<GameObject> _settingUIToggleGameObject1;
	shared_ptr<Transform> _settingUIToggleTransform1;
	shared_ptr<UICheckBox> _settingUICheckBox1;

	// Toggle #2
	shared_ptr<GameObject> _settingUIToggleGameObject2;
	shared_ptr<Transform> _settingUIToggleTransform2;
	shared_ptr<UICheckBox> _settingUICheckBox2;

	// Button #3
	shared_ptr<GameObject> _settingUICloseGameObject;
	shared_ptr<Transform> _settingUICloseTransform;
	shared_ptr<UIButton> _settingUICloseButton;

	// Icon #1
	shared_ptr<GameObject> _closeIconGameObject1;
	shared_ptr<Transform> _closeIconTransform1;
	shared_ptr<UIImage> _closeIcon1;

	// Icon #2
	shared_ptr<GameObject> _closeIconGameObject2;
	shared_ptr<Transform> _closeIconTransform2;
	shared_ptr<UIImage> _closeIcon2;

	// Icon #3
	shared_ptr<GameObject> _closeIconGameObject3;
	shared_ptr<Transform> _closeIconTransform3;
	shared_ptr<UIImage> _closeIcon3;

#pragma endregion

	// Canvas
	shared_ptr<GameObject> _settingUIGameObject;
	shared_ptr<UICanvas> _uiCanvas;
	shared_ptr<Transform> _uiCanvasTransform;
};

