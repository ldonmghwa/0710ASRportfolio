#include "common.h"

GunMinion::GunMinion(wstring _wstr, 
	Character* _player,
	vector<Character*> _target,
	GunType _type)
	: ASRGun(_wstr, _player, _target, _type)
{
	isClbarAvailable = false;
	bulletNum = 3;
	curBulletNum = bulletNum;
	bulletPower = 100.0f;
	reloadTime = 5.0f;
	backUpReloadTime = reloadTime;
	reloadPerSec = (reloadTime - 0.1f) / bulletNum;
	backUpReloadPerSec = reloadPerSec;
	shotSDKey = "MinionGunShot";
	reloadSDKey = "MinionGunReload";
	SOUND->AddSound("ArmorGunB_Shot_01.wav", shotSDKey);
	SOUND->AddSound("ArmorGunB_Reload_01.wav", reloadSDKey);
}

GunMinion::~GunMinion()
{
	TEXTURE->DeleteTexture(L"BulletKin_Bullet_Death.png");
	SOUND->DeleteSound(shotSDKey);
	SOUND->DeleteSound(reloadSDKey);
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
