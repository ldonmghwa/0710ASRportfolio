#pragma once
enum HPBarState {
	ZERO,
	HALF,
	FULL
};
enum class CRState {
	IDLE,
	IDLEWP,
	WALK,
	WALKWP,
	ROLL,
	DEATH,
	HIT,
	SIZE
};

enum class CharType {
	PLAYABLE,
	MONSTER
	//NONEPLAY
};

enum class ItemType {
	WEAPON,
	CONSUM,
	STUFF
};

enum class GunType {
	BASIC,
	GUIDE,
	MINION
};

enum class PLType {
	PLCONVICT,
	PLBULLET
};

enum class MTType {
	MTMINION,
	BOSS
};

struct HPBar {
	ObImage* heartBar[3];
	int hpBarState;
	HPBar() {
		hpBarState = HPBarState::FULL;
		heartBar[0] = new ObImage(L"HeartBarFull.png");
		heartBar[1] = new ObImage(L"HeartBarHalf.png");
		heartBar[2] = new ObImage(L"HeartBarZero.png");

		for (int i = 0; i < 3; i++) {
			heartBar[i]->scale.x = heartBar[i]->imageSize.x * 5.0f;
			heartBar[i]->scale.y = heartBar[i]->imageSize.y * 5.0f;
		}
	}
	~HPBar() {
		for (int i = 0; i < 3; i++) delete heartBar[i];
	}
};
struct BBBar {
	ObImage* blankBulletBar[2];
	int bBarState;
	BBBar() {
		bBarState = 1;
		blankBulletBar[0] = new ObImage(L"BlankBulletFull.png");
		blankBulletBar[1] = new ObImage(L"BlankBulletZero.png");

		for (int i = 0; i < 2; i++) {
			blankBulletBar[i]->scale.x = blankBulletBar[i]->imageSize.x * 4.0f;
			blankBulletBar[i]->scale.y = blankBulletBar[i]->imageSize.y * 4.0f;
		}
	}
	~BBBar() {
		for (int i = 0; i < 2; i++) delete blankBulletBar[i];
	}
};
struct CLBar {
	ObImage* cylinderBar[2];
	int cBarState;
	CLBar() {
		cBarState = 1;
		cylinderBar[0] = new ObImage(L"BasicBulletFull.png");
		cylinderBar[1] = new ObImage(L"BasicBulletZero.png");
		for (int i = 0; i < 2; i++) {
			cylinderBar[i]->scale.x = cylinderBar[i]->imageSize.x * 0.8f;
			cylinderBar[i]->scale.y = cylinderBar[i]->imageSize.y * 0.8f;
		}
	}
	~CLBar() {
		for (int i = 0; i < 2; i++) delete cylinderBar[i];
	}
};