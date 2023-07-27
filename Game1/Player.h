#pragma once

class Player : public Character
{
private:
	ObImage* idleWithWeapon;
	ObImage* walkWithWeapon;
	ObImage* dodgeRoll;
	enum class PLType			playerType;
	vector<class ASRGun*> gunVector;

	Vector2			beforeDashPoint;

	bool			isCarryWP;
	int				gunNum;
	int				selectWPNum;

	float			rollTime;
public:
	Player();
	Player(PLType _type);
	~Player();

	void Init(Vector2 spawn);
	void Control();
	void Update();
	void Render();

	void GoBack();
	void LookTarget(Vector2 target);
	void GetFromChest(enum class GunType _type);


};

//class Sloider : public Player
//{
//
//};