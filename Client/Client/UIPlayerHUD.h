#pragma once
#include "Engine\Prefab.h"

class UIPlayerHUD : public Prefab
{
public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;

private:
	
	// Score
	shared_ptr<GameObject> _scoreTextGameObject;
	shared_ptr<UIText> _scoreText;
	shared_ptr<Transform> _scoreTextTransform;

#pragma region 
	// Score number
	shared_ptr<GameObject> _scoreNumTextGameObject1;
	shared_ptr<UIText> _scoreNumText1;
	shared_ptr<Transform> _scoreNumTextTransform1;

	vector<shared_ptr<GameObject>> _scoreNumTextObjects;
	vector<shared_ptr<UIText>> _scoreNumText;
	vector<shared_ptr<Transform>> _scoreNumtextTransform;

	// No weapon text
	shared_ptr<GameObject> _noWeaponTextGameObject;
	shared_ptr<UIText> _noWeaponText;
	shared_ptr<Transform> _noWeaponTextGameTransform;

	// Ammo number
	shared_ptr<GameObject> _ammoTextGameObject;
	shared_ptr<UIText> _ammoText;
	shared_ptr<Transform> _ammoTextTransform;

	// Durability number
	shared_ptr<GameObject> _durabilityTextGameObject;
	shared_ptr<UIText> _durabilityText;
	shared_ptr<Transform> _durabilityTextTransform;

	// Canvas
	shared_ptr<GameObject> _mainHUDCanvas;
	shared_ptr<UICanvas> _uiCanvas;
	shared_ptr<Transform> _uiCanvasTransform;
};

