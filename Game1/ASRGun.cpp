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
}

ASRGun::~ASRGun()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) delete (*it);
}

void ASRGun::Update()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		if ((*it)->IsBulletReach()) {

		}
		(*it)->Update();
	}
	img->Update();
}

void ASRGun::Render()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) (*it)->Render();	
	img->Render();
}

void ASRGun::FireBullet()
{
}