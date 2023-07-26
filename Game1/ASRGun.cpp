#include "common.h"

ASRGun::ASRGun(wstring _wstr, ObRect* _player,
	GunType _type)
{
	gunType = _type;
	gunFileName = _wstr;
	type = ItemType::WEAPON;
	img = new ObImage(_wstr);
	img->scale.x = img->imageSize.x * 2.0f;
	img->scale.y = img->imageSize.y * 2.0f;
	img->SetParentT(*_player);
	img->SetLocalPosX(-_player->scale.x * 0.4f);
	img->SetLocalPosY(_player->scale.y * 0.5f);
	img->pivot = OFFSET_LB;
	if (gunType == GunType::BASIC) {
		bulletNum = 10;
		bulletPower = 400.0f;
	}
	else if (gunType == GunType::GUIDE) {
		bulletNum = 3;
		bulletPower = 400.0f;
	}
}

ASRGun::~ASRGun()
{
	for (auto it = bulletCylider.begin(); it != bulletCylider.end(); it++) delete (*it);
}

void ASRGun::Update()
{
	for (int i = 0; i < bulletNum; i++) bulletCylider[i]->Update();
	img->Update();
}

void ASRGun::Render()
{
	for (int i = 0; i < bulletNum; i++) bulletCylider[i]->Render();
	img->Render();
}

void ASRGun::FireBullet()
{
	bulletCylider.push_back(new ASRBullet())
}