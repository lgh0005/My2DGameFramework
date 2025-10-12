#pragma once
#include "Engine\Prefab.h"

class Player : public Prefab
{
	using Super = Prefab;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;

private:
	void CreateFlipbookNormal();
	void CreateFlipbookGun();
	void CreateFlipbookSword();

/*==========================
//    Player Flipbooks    //
//========================*/
private:
#pragma region PLAYER_FLIPBOOK_NORMAL
	shared_ptr<Flipbook> _normal_climb;
	shared_ptr<Flipbook> _normal_combo_1_r;
	shared_ptr<Flipbook> _normal_combo_1_l;
	shared_ptr<Flipbook> _normal_combo_2_r;
	shared_ptr<Flipbook> _normal_combo_2_l;
	shared_ptr<Flipbook> _normal_combo_3_r;
	shared_ptr<Flipbook> _normal_combo_3_l;
	shared_ptr<Flipbook> _normal_damaged_r;
	shared_ptr<Flipbook> _normal_damaged_l;
	shared_ptr<Flipbook> _normal_dash_r;
	shared_ptr<Flipbook> _normal_dash_l;
	shared_ptr<Flipbook> _normal_died_r;
	shared_ptr<Flipbook> _normal_died_l;
	shared_ptr<Flipbook> _normal_fall_r;
	shared_ptr<Flipbook> _normal_fall_l;
	shared_ptr<Flipbook> _normal_idle_r;
	shared_ptr<Flipbook> _normal_idle_l;
	shared_ptr<Flipbook> _normal_jump_r;
	shared_ptr<Flipbook> _normal_jump_l;
	shared_ptr<Flipbook> _normal_run_r;
	shared_ptr<Flipbook> _normal_run_l;
	shared_ptr<Flipbook> _normal_slide_r;
	shared_ptr<Flipbook> _normal_slide_l;
	shared_ptr<Flipbook> _normal_walk_r;
	shared_ptr<Flipbook> _normal_walk_l;
	shared_ptr<Flipbook> _normal_wallslide_r;
	shared_ptr<Flipbook> _normal_wallslide_l;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_GUN
	shared_ptr<Flipbook> _gun_climb;
	shared_ptr<Flipbook> _gun_air_attack_r;
	shared_ptr<Flipbook> _gun_air_attack_l;
	shared_ptr<Flipbook> _gun_damaged_r;
	shared_ptr<Flipbook> _gun_damaged_l;
	shared_ptr<Flipbook> _gun_dash_r;
	shared_ptr<Flipbook> _gun_dash_l;
	shared_ptr<Flipbook> _gun_died_r;
	shared_ptr<Flipbook> _gun_died_l;
	shared_ptr<Flipbook> _gun_idle_r;
	shared_ptr<Flipbook> _gun_idle_l;
	shared_ptr<Flipbook> _gun_jump_r;
	shared_ptr<Flipbook> _gun_jump_l;
	shared_ptr<Flipbook> _gun_run_r;
	shared_ptr<Flipbook> _gun_run_l;
	shared_ptr<Flipbook> _gun_shot_r;
	shared_ptr<Flipbook> _gun_shot_l;
	shared_ptr<Flipbook> _gun_slide_r;
	shared_ptr<Flipbook> _gun_slide_l;
	shared_ptr<Flipbook> _gun_walk_r;
	shared_ptr<Flipbook> _gun_walk_l;
	shared_ptr<Flipbook> _gun_wallslide_r;
	shared_ptr<Flipbook> _gun_wallslide_l;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_SWORD
	shared_ptr<Flipbook> _sword_climb;
	shared_ptr<Flipbook> _sword_combo_1_r;
	shared_ptr<Flipbook> _sword_combo_1_l;
	shared_ptr<Flipbook> _sword_combo_2_r;
	shared_ptr<Flipbook> _sword_combo_2_l;
	shared_ptr<Flipbook> _sword_combo_3_r;
	shared_ptr<Flipbook> _sword_combo_3_l;
	shared_ptr<Flipbook> _sword_damaged_r;
	shared_ptr<Flipbook> _sword_damaged_l;
	shared_ptr<Flipbook> _sword_dash_r;
	shared_ptr<Flipbook> _sword_dash_l;
	shared_ptr<Flipbook> _sword_died_r;
	shared_ptr<Flipbook> _sword_died_l;
	shared_ptr<Flipbook> _sword_fall_r;
	shared_ptr<Flipbook> _sword_fall_l;
	shared_ptr<Flipbook> _sword_idle_r;
	shared_ptr<Flipbook> _sword_idle_l;
	shared_ptr<Flipbook> _sword_jump_r;
	shared_ptr<Flipbook> _sword_jump_l;
	shared_ptr<Flipbook> _sword_run_r;
	shared_ptr<Flipbook> _sword_run_l;
	shared_ptr<Flipbook> _sword_slide_r;
	shared_ptr<Flipbook> _sword_slide_l;
	shared_ptr<Flipbook> _sword_walk_r;
	shared_ptr<Flipbook> _sword_walk_l;
	shared_ptr<Flipbook> _sword_wallslide_r;
	shared_ptr<Flipbook> _sword_wallslide_l;
#pragma endregion
};

