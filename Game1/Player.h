#pragma once

class Player : public Character
{
private:
	class GameGUI*			plgui;
	enum class PLType		playerType;
	vector<class ASRGun*>	gunVector;

	Vector2					backUpDashPoint;
	Vector2					rollDistance;

	bool					isCarryWP;
	bool					isAiming;
	bool					isGunReloading;
	int						gunNum;
	int						selectWPNum;
	int clickcount;

	float					rollTime;
	float					reloadPerSec;
	float					backUpReloadPerSec;
	float					rollWeight;
	float					rollWeightScale;
	float					backUpRollWeight;
public:
	Player(string _name);
	Player(string _name, PLType _type);
	~Player();

	void Init();
	void Control();
	void Update();
	void Render();

	void GoBack();
	void NumberKeyInput();
	void TakeDamage(int _damagePoint) override;
	void LookTarget(Vector2 target);
	void GetFromChest(GunType _type);
	void SetGui(class GameGUI* _plgui) { plgui = _plgui; }

	int GetCurrentBulletNum(){ return gunVector[selectWPNum]->GetBulletNum(); }

};

//class Sloider : public Player
//{
//
//};