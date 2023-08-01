#include "common.h"

ASRGun::ASRGun(wstring _wstr,
	Character* _player,
	vector<Character*> _target, 
	GunType _type) : Item()
{
	gunType = _type;
	gunFileName = _wstr;
	target = _target;
	type = ItemType::WEAPON;
	parentChar = _player;
	resizeScale = 2.0f;

	img = new ObImage(_wstr);
	img->scale.x = img->imageSize.x * resizeScale;
	img->scale.y = img->imageSize.y * resizeScale;
	
	col->scale = img->scale;
	col->isFilled = false;
	img->SetParentRT(*col);
	col->SetParentT(*_player->GetCol());
	col->SetLocalPosX(-_player->GetCol()->scale.x * 0.4f);
	col->SetLocalPosY(_player->GetCol()->scale.y * 0.5f);
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
	for (int i = 0;
		i < bulletCylinder.size(); i++) {
		if (!bulletCylinder[i]->GetIsFire() && bulletCylinder[i]->GetDeathImgAniStop()) {
			bulletCylinder.erase(bulletCylinder.begin() + i);
			break;
		}
	}
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		(*it)->IsBulletReach(target);
		(*it)->Update();
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