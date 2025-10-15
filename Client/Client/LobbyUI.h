#pragma once
#include "Engine\Prefab.h"

class UIBlocker;
class StartButtonScript;
class OptionButtonScript;
class QuitButtonScript;

class LobbyUI : public Prefab
{
	using Super = Prefab;

public:
	LobbyUI(const string& name);
	virtual ~LobbyUI() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;

private:
	
	// UI Blocker
	shared_ptr<GameObject> _uiBlocker;
	shared_ptr<Transform> _uiBlockerTransform;
	shared_ptr<UIBlocker> _uiBlockerScript;

	// Title Text #1
	shared_ptr<GameObject> _title1;
	shared_ptr<Transform> _title1Transform;
	shared_ptr<UIText> _title1Text;

	// Title Text #2
	shared_ptr<GameObject> _title2;
	shared_ptr<Transform> _title2Transform;
	shared_ptr<UIText> _title2Text;

	// Button #1
	shared_ptr<GameObject> _button1;
	shared_ptr<Transform> _button1Transform;
	shared_ptr<UIButton> _button1Button;
	shared_ptr<UIText> _button1Text;
	shared_ptr<StartButtonScript> _button1Script;

	// Button #2
	shared_ptr<GameObject> _button2;
	shared_ptr<Transform> _button2Transform;
	shared_ptr<UIButton> _button2Button;
	shared_ptr<UIText> _button2Text;
	shared_ptr<OptionButtonScript> _button2Script;
	
	// Button #3
	shared_ptr<GameObject> _button3;
	shared_ptr<Transform> _button3Transform;
	shared_ptr<UIButton> _button3Button;
	shared_ptr<UIText> _button3Text;
	shared_ptr<QuitButtonScript> _button3Script;

	// Canvas
	shared_ptr<GameObject> _mainUI;
	shared_ptr<Transform> _mainUITransform;
	shared_ptr<UICanvas> _mainUIComponent;
};

