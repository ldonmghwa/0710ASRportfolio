#include "common.h"

GunGuided::GunGuided(wstring _wstr
	, Character* _player
	, vector<Character*> _target
	, GunType _type)
	: ASRGun(_wstr, _player, _target, _type)
{
	bulletNum = 3;
	curBulletNum = bulletNum;
	bulletPower = 600.0f;
	backUpReloadTime = 3.0f;
	reloadTime = 3.0f;
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
	if (isCylinderEmpty) return;
	bulletCylinder.push_back(new ASRGuided(L"Convict_Gun2_Bullet.png", _destPos, this->col, bulletPower));
	bulletCylinder.back()->SetBulletDeathImg(L"Convict_Gun2_Bullet_Death.png");
	ASRGun::FireBullet();
}
