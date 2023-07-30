#pragma once
#define HPMAX 5
#define BBMAX 5
class GameGUI
{
private:
	class HPBar* hpBar[HPMAX];
	class BBBar* bbBar[BBMAX];

	ObImage* cylinderBarTP[2];
	ObImage* boxKeyImg;
	ObImage* moneyImg;
	vector<class CLBar*> clBar;

	Camera* uiCam;
	RECT boxKeyRc;

	int basicBulletNum;
	int beforeBasicBulletNum;
	int guideBulletNum;
	int curMaxHPBar;
	int curHPIdx;
	int curMaxBBBar;
	int curBBIdx;
	int curCLIdx;
	int boxKeyNum;
	int moneyNum;

public:
	GameGUI();
	~GameGUI();

	void Init(int _bulletNum);
	void Update();
	void Render();

	void ConsumeBullet(bool isCylinderEmpty);
	void ReLoadingBulletBar(float& reloadPerSec, float reloadTime);
	void ReduceHPBar();
	void ReduceBBBar();
	void IncreaseMoneyBar();
};

