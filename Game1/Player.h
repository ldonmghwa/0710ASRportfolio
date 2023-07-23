#pragma once
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
	ObImage*		charImg[PLState::PLSIZE];
	vector<class ASRGun*> gunVector;
	enum class PLType			type;

	Vector2			controlDir;
	Vector2			dir2;
	Vector2			beforeDashPoint;
	Vector2			lastPos;

	bool			isCarryWP;

	int				state;
	int				dirFrame[8];
	int				gunNum;

	float			speed;
	float			rollTime;
public:
	Player();
	Player(PLType _type);
	virtual ~Player();

	void Init(Vector2 spawn);
	void Control();
	void Update() override;
	void Render() override;

	void GoBack();
	void LookTarget(Vector2 target);
	void GetFromChest(enum class GunType _type);

	Vector2 GetFoot();
};

//class Sloider : public Player
//{
//
//};