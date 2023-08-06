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

	isAiming = false;
	isReloading = false; 
	isCylinderEmpty = false;
}

ASRGun::~ASRGun()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) delete (*it);
	for (int i = 0; i < 2; i++)delete cylinderBarTP[i];
	for (auto it = clbarList.begin(); it != clbarList.end(); it++) delete (*it);

	TEXTURE->DeleteTexture(L"BasicBulletFull.png");
	TEXTURE->DeleteTexture(L"BasicBulletZero.png");

	TEXTURE->DeleteTexture(L"CylinderUp.png");
	TEXTURE->DeleteTexture(L"CylinderDown.png");
}
void ASRGun::Update()
{
	for (int i = 0;
		i < bulletCylinder.size(); i++) {
		if (!bulletCylinder[i]->GetIsFire()&& bulletCylinder[i]->GetDeathImgAniStop()) {
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
	if (isVisible) {
		if (isClbarAvailable) {
			for (int i = 0; i < clbarList.size(); i++)
			{
				clbarList[i]->cylinderBar[0]->SetWorldPosX(CAM->position.x + 785.0f);
				clbarList[i]->cylinderBar[0]->SetWorldPosY(CAM->position.y - 475.0f + i * 15.0f);
				clbarList[i]->cylinderBar[1]->SetWorldPosX(CAM->position.x + 785.0f);
				clbarList[i]->cylinderBar[1]->SetWorldPosY(CAM->position.y - 475.0f + i * 15.0f);
				clbarList[i]->cylinderBar[0]->Update();
				clbarList[i]->cylinderBar[1]->Update();
			}
			cylinderBarTP[0]->SetWorldPosX(CAM->position.x + 785.0f);
			cylinderBarTP[0]->SetWorldPosY(CAM->position.y - 475.0f + clbarList.size() * 15.0f);
			cylinderBarTP[1]->SetWorldPosX(CAM->position.x + 785.0f);
			cylinderBarTP[1]->SetWorldPosY(CAM->position.y - 490.0f);
			cylinderBarTP[0]->Update();
			cylinderBarTP[1]->Update();
		}
		Item::Update();
		img->Update();
	}

}

void ASRGun::Render()
{
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++)
	{
		(*it)->Render();
	}
	if (isVisible) {
		if (isClbarAvailable) {
			for (auto it = clbarList.begin(); it != clbarList.end(); it++) {
				if ((*it)->cBarState == 1) (*it)->cylinderBar[0]->Render();
				else if ((*it)->cBarState == 0) (*it)->cylinderBar[1]->Render();
			}
			cylinderBarTP[0]->Render();
			cylinderBarTP[1]->Render();
		}
		Item::Render();
		img->Render();
	}
}

void ASRGun::FireBullet()
{
	if(clbarList.size()>0) ReduceClbarImg();
	curBulletNum--;
	if (curBulletNum <= 0) isCylinderEmpty = true;
}

void ASRGun::GunReLoading()
{
	reloadTime -= DELTA;
	if (clbarList.size() > 0)ReloadingClbarImg();
	if (reloadTime < 0.0f) {
		reloadTime = backUpReloadTime;
		curBulletNum = bulletNum;
		isCylinderEmpty = false;
		isReloading = false;
	}
}

void ASRGun::GunReLoading(bool& isGunReloading)
{
	reloadTime -= DELTA;
	if (clbarList.size() > 0)ReloadingClbarImg();
	if (reloadTime < 0.0f) {
		reloadTime = backUpReloadTime;
		curBulletNum = bulletNum;
		isCylinderEmpty = false;
		isReloading = false;
		isGunReloading = false;
	}
}

void ASRGun::ReduceClbarImg()
{
	if (isCylinderEmpty) return;
	curCLIdx = curBulletNum - 1;
	if (clbarList[curCLIdx]->cBarState == 0) curCLIdx--;
	if (curCLIdx < 0) curCLIdx = 0;
	clbarList[curCLIdx]->cBarState -= 1;
	if (clbarList[curCLIdx]->cBarState < 0)clbarList[curCLIdx]->cBarState = 0;
}

void ASRGun::ReloadingClbarImg()
{
	//if (!isCylinderEmpty) return;
	reloadPerSec -= DELTA;
	if (reloadPerSec < 0.0f) {
		clbarList[curCLIdx]->cBarState = 1;
		curCLIdx++;
		reloadPerSec = backUpReloadPerSec;
		if (curCLIdx == clbarList.size()) curCLIdx--;
	}
}
