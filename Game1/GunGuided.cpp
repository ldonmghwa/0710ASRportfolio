#include "common.h"

GunGuided::GunGuided(wstring _wstr
	, ObRect* _player
	, GunType _type) 
	: ASRGun(_wstr, _player, _type)
{
	bulletNum = 3;
	beforeBulletNum = 3;
	bulletPower = 600.0f;
	beforeReloadTime = 3.0f;
}

GunGuided::~GunGuided()
{
}

void GunGuided::Update()
{
	ASRGun::Update();
}

void GunGuided::Render()
{
	ASRGun::Render();
}

void GunGuided::FireBullet(Vector2 _destPos)
{
	if (!isReloading)
		bulletCylinder.push_back(new ASRGuided(L"Convict_Gun2_Bullet.png", _destPos));
	ASRGun::FireBullet();
}
