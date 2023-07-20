#pragma once
enum PLType {
	PLCONVICT,
	PLBULLET
};
enum PLState {
	PLIDLE,
	PLIDLEWP,
	PLWALK,
	PLWALKWP,
	PLROLL,
	PLDEATH,
	//PLDEATH2,
	PLSIZE
};

class Player : public ObRect
{
	ObImage* charImg[PLState::PLSIZE];
	int state;
	int dirFrame[8];

	Vector2		controlDir;
	Vector2		dir2;
	Vector2		beforeDashPoint;
	float		speed;
	float rollTime;
	Vector2 lastPos;
	//시계프레임
public:
	Player();
	Player(PLType type);
	virtual ~Player();
	void Init(Vector2 spawn);
	void Control();
	void Update() override;
	void Render() override;
	void LookTarget(Vector2 target);
	Vector2 GetFoot();
	void GoBack();
};

//class Sloider : public Player
//{
//
//};