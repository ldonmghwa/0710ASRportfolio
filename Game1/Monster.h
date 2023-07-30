#pragma once
class Monster : public Character
{
private:
	enum class MTType monsterType;
	class GunMinion* gun;

	float attackRange;
	float detectionRange;
	float shootingInterval;
public:
	Monster();
	~Monster();

	void Init(Vector2 spawn);
	void Control();
	void Update();
	void Render();

	void GoBack();
	void LookTarget(Vector2 target);
	
	class GunMinion* GetGun() { return gun; }
};

