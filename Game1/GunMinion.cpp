#include "common.h"

GunMinion::GunMinion(wstring _wstr, 
	Character* _player,
	vector<Character*> _target,
	GunType _type)
	: ASRGun(_wstr, _player, _target, _type)
{
	bulletNum = 10;
	curBulletNum = bulletNum;
	bulletPower = 200.0f;
	backUpReloadTime = 3.0f;
	reloadTime = 3.0f;
}

GunMinion::~GunMinion()
{
	TEXTURE->DeleteTexture(L"BulletKin_Bullet_Death.png");
}

void GunMinion::Update()
{
	ASRGun::Update();
}

void GunMinion::Render()
{
	ASRGun::Render();
}

void GunMinion::FireBullet()
{
	if (isCylinderEmpty) return;
	bulletCylinder.push_back(
		new BulletMinion(L"BulletKin_Bullet.png", 
			this->col, 
			bulletPower,
			L"BulletKin_Bullet_Death.png")
	);
	ASRGun::FireBullet();
}
