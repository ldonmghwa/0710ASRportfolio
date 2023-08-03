#pragma once
#define HPMAX 5
#define BBMAX 5
class GameGUI
{
private:
	class HPBar* hpBar[HPMAX];
	class BBBar* bbBar[BBMAX];

	ObImage* boxKeyImg;
	ObImage* moneyImg;

	Camera* uiCam;
	RECT boxKeyRc;

	int basicBulletNum;
	int backUpBasicBulletNum;
	int guideBulletNum;
	int curMaxHPBar;
	int curHPIdx;
	int curMaxBBBar;
	int curBBIdx;
	int boxKeyNum;
	int moneyNum;

public:
	GameGUI();
	~GameGUI();

	void Init(int _bulletNum);
	void Update();
	void Render();

	void ReduceHPBar();
	void ReduceBBBar();
	void IncreaseMoneyBar();
};

