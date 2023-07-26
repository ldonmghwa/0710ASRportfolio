#pragma once

class Player : public Character
{
	ObImage* idleWithWeapon;
	ObImage* walkWithWeapon;
	ObImage* dodgeRoll;
	vector<class ASRGun*> gunVector;
	enum class PLType			playerType;

	Vector2			beforeDashPoint;

	bool			isCarryWP;
	int				gunNum;
	int				selectWPNum;

	float			rollTime;
public:
	Player(PLType _type);
	~Player();

	void Init(Vector2 spawn);
	void Control() override;
	void Update() override;
	void Render() override;

	void GoBack();
	void LookTarget(Vector2 target);
	void GetFromChest(enum class GunType _type);


};

//class Sloider : public Player
//{
//
//};