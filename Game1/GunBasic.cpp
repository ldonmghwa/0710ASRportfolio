#include "common.h"

GunBasic::GunBasic(wstring _wstr
	, ObRect* _player
	, vector<GameObject*> _target
	, GunType _type)
	: ASRGun(_wstr, _player, _target, _type)
{
	bulletNum = 10;
	curBulletNum = bulletNum;
	bulletPower = 400.0f;
	backUpReloadTime = 2.0f;
	reloadTime = 2.0f;
}

GunBasic::~GunBasic()
{
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
	bulletCylinder.push_back(new ASRBullet(L"Convict_Gun1_Bullet.png", this->col, bulletPower));
	ASRGun::FireBullet();
}
