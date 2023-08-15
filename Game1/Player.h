#pragma once

class Player : public Character
{
private:
	class GameGUI*			plgui;
	enum class PLType		playerType;
	vector<class ASRGun*>	gunVector;

	ObRect*				col2;

	Vector2					backUpDashPoint;
	Vector2					rollDistance;
	
	Int2					plIdx;
	Int2					lastPlIdx;

	bool					isCarryWP;
	bool					isAiming;
	bool					isGunReloading;
	bool					isBBTime;
	bool					isHittingOn;
	bool					isLightening;

	int						selectWPNum;
	int						blankBulletNum;
	int						maxBlankBulletNum;

	float					rollTime;
	float					backUpRollTime;
	float					reloadPerSec;
	float					backUpReloadPerSec;
	float					rollWeight;
	float					rollWeightScale;
	float					backUpRollWeight;
	float					blankBulletTime;
	float					backUpBlankBulletTime;
	float					bloodingTime;
	float					backUpBloodingTime;
public:
	int						gunNum;
	int						chestKeyNum;
public:
	Player(string _name);
	Player(string _name, PLType _type);
	~Player();

	void Init();
	void Control();
	void Control1();
	void Update();
	void Render();

	void GoBack();
	void TakeDamage(int _damagePoint) override;
	void LookTarget(Vector2 target);
	void GetFromChest(GunType _type);
	void SetGui(class GameGUI* _plgui) { plgui = _plgui; }

	void AddHp();
	void AddBlankBullet();

	int GetCurrentBulletNum(){ return gunVector[selectWPNum]->GetBulletNum(); }

};

//class Sloider : public Player
//{
//
//};