#pragma once
class Monster : public Character
{
private:
	enum class MTType monsterType;
	class GunMinion* gun;

	float attackRange;
	float detectionRange;
	float shootingInterval;
	float weight;

	Vector2 dest;
	Vector2 source;
public:
	Monster();
	~Monster();

	void Init();
	void Control();
	void Update();
	void Render();

	void GoBack();
	void SearchPlayer();
	void LookTarget(Vector2 target);
	
	class GunMinion* GetGun() { return gun; }
};

