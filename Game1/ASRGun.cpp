#include "common.h"

ASRGun::ASRGun(wstring _wstr, ObRect* _player,
	vector<GameObject*> _target, GunType _type) : Item()
{
	gunType = _type;
	gunFileName = _wstr;
	target = _target;
	type = ItemType::WEAPON;
	resizeValue = 2.0f;
	img = new ObImage(_wstr);
	img->scale.x = img->imageSize.x * resizeValue;
	img->scale.y = img->imageSize.y * resizeValue;
	col->scale = img->scale;
	col->isFilled = false;
	img->SetParentRT(*col);
	col->SetParentT(*_player);
	col->SetLocalPosX(-_player->scale.x * 0.4f);
	col->SetLocalPosY(_player->scale.y * 0.5f);
	img->pivot = OFFSET_LB;
	col->pivot = OFFSET_LB;
	isReloading = false; 
	isCylinderEmpty = false;
}

ASRGun::~ASRGun()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) delete (*it);
}

void ASRGun::Update()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		if (!(*it)->GetIsFire()) {
			bulletCylinder.erase(it);
			break;
		}
	}
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		if ((*it)->IsBulletReach(target)) {
			(*it)->Update();
		}
	}
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		if ((*it)->IsBulletReach()) {
			(*it)->Update();
		}
		
	}
	
	Item::Update();
	img->Update();
}

void ASRGun::Render()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) (*it)->Render();	
	Item::Render();
	img->Render();
}

void ASRGun::FireBullet()
{
	curBulletNum--;
	if (curBulletNum <= 0) isCylinderEmpty = true;
}

void ASRGun::GunReLoading()
{
	reloadTime -= DELTA;
	if (reloadTime < 0.0f) {
		reloadTime = backUpReloadTime;
		curBulletNum = bulletNum;
		isCylinderEmpty = false;
		isReloading = false;
	}
}
