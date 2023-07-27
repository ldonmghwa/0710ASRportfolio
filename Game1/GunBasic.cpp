#include "common.h"

GunBasic::GunBasic(wstring _wstr
	, ObRect* _player
	, GunType _type) 
	: ASRGun(_wstr, _player, _type)
{
	bulletNum = 10;
	beforeBulletNum = 10;
	bulletPower = 400.0f;
	beforeReloadTime = 2.0f;
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
	if (!isReloading) {
		bulletCylinder.push_back(new ASRBullet(L"Convict_Gun1_Bullet.png"));
	}
	ASRGun::FireBullet();
}
