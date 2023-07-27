#include "common.h"
#include "GunGuided.h"

GunGuided::GunGuided(wstring _wstr, ObRect* _player,
	GunType _type) : ASRGun(_wstr, _player, _type)
{
	bulletNum = 3;
	bulletPower = 600.0f;
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

void GunGuided::FireBullet()
{
	bulletCylinder.push_back(new ASRGuided(L"Convict_Gun2_Bullet.png"));
	bulletCylinder[bulletCylinder.size() - 1]->Fire(this->col, bulletPower);
}
