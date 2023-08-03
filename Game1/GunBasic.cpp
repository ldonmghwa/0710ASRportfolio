#include "common.h"

GunBasic::GunBasic(wstring _wstr,
	Character* _player,
	vector<Character*> _target,
	GunType _type)
	: ASRGun(_wstr, _player, _target, _type)
{
	isClbarAvailable = true;
	bulletNum = 10;
	curBulletNum = bulletNum; 
	curCLIdx = curBulletNum - 1;

	bulletPower = 400.0f;
	reloadTime = 2.0f;
	backUpReloadTime = reloadTime;
	reloadPerSec = (reloadTime - 0.1f) / bulletNum;
	backUpReloadPerSec = reloadPerSec;

	cylinderBarTP[0] = new ObImage(L"CylinderUp.png");
	cylinderBarTP[1] = new ObImage(L"CylinderDown.png");
	for (int i = 0; i < 2; i++) {
		cylinderBarTP[i]->scale.x = cylinderBarTP[i]->imageSize.x;
		cylinderBarTP[i]->scale.y = cylinderBarTP[i]->imageSize.y;
	}

	for (int i = 0; i < bulletNum; i++) clbarList.push_back(new CLBar());
}

GunBasic::~GunBasic()
{
	TEXTURE->DeleteTexture(L"Convict_Gun1_Bullet_Death.png");
}

void GunBasic::Update()
{
	ASRGun::Update();
}

void GunBasic::Render()
{
	ASRGun::Render();
}

void GunBasic::FireBullet()
{
	if (isCylinderEmpty) return;
	bulletCylinder.push_back(
		new ASRBullet(L"Convict_Gun1_Bullet.png",
			this->col,
			bulletPower,
			 L"Convict_Gun1_Bullet_Death.png")
	);
	ASRGun::FireBullet();
}
