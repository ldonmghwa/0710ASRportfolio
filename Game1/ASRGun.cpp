#include "common.h"

ASRGun::ASRGun(wstring _wstr, ObRect* _player,
	GunType _type) : Item()
{
	gunType = _type;
	gunFileName = _wstr;
	type = ItemType::WEAPON;
	img = new ObImage(_wstr);
	img->scale.x = img->imageSize.x * 2.0f;
	img->scale.y = img->imageSize.y * 2.0f;
	col->scale = img->scale;
	col->isFilled = false;
	img->SetParentRT(*col);
	col->SetParentT(*_player);
	col->SetLocalPosX(-_player->scale.x * 0.4f);
	col->SetLocalPosY(_player->scale.y * 0.5f);
	img->pivot = OFFSET_LB;
	col->pivot = OFFSET_LB;
	isReloading = false;
}

ASRGun::~ASRGun()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) delete (*it);
}

void ASRGun::Update()
{
	if (isReloading) {
		reloadTime -= DELTA;
		if (reloadTime < 0.0f) {
			reloadTime = beforeReloadTime;
			bulletNum = beforeBulletNum;
			isReloading = false;
		}
	}
	ImGui::Text("%f, %f", col->GetWorldPos().x, col->GetWorldPos().y);
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		if (!(*it)->IsBulletReach())
			(*it)->Release();
		else 
			(*it)->Update();
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
	if (!isReloading) {
		bulletCylinder[bulletCylinder.size()-1]->Fire(this->col, bulletPower);
		bulletNum--;
		if (bulletNum < 0) isReloading = true;
	}
}
