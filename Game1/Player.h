#pragma once

class Player : public Character
{
private:
	class GameGUI*			plgui;
	enum class PLType		playerType;
	vector<class ASRGun*>	gunVector;

	Vector2					backUpDashPoint;

	bool					isCarryWP;
	int						gunNum;
	int						selectWPNum;

	float					rollTime;
	float					reloadPerSec;
	float					backUpReloadPerSec;
	float					rollWeight;
	float					rollWeightScale;
	float					backUpRollWeight;
public:
	Player();
	Player(PLType _type);
	~Player();

	void Init();
	void Control();
	void Update();
	void Render();

	void GoBack();
	void TakeDamage() override;
	void LookTarget(Vector2 target);
	void GetFromChest(GunType _type);
	void SetGui(class GameGUI* _plgui) { plgui = _plgui; }

	int GetCurrentBulletNum(){ return gunVector[selectWPNum]->GetBulletNum(); }

};

//class Sloider : public Player
//{
//
//};