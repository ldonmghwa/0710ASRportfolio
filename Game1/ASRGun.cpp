#include "stdafx.h"
#include "GUIStruct.h"
#include "Player.h"
#include "ASRBullet.h"
#include "ASRGun.h"

ASRGun::ASRGun(wstring _wstr, Player* _player) : ObImage(_wstr)
{
	if (_wstr == L"Convict_Gun1.png") {
		type = GunType::BASIC;
		this->scale.x = this->imageSize.x * 2.0f;
		this->scale.y = this->imageSize.y * 2.0f;
		this->SetParentT(*_player);
		this->SetLocalPosX(-_player->scale.x * 0.4f);
		this->SetLocalPosY(_player->scale.y * 0.5f);
		this->pivot = OFFSET_LB;
		bulletNum = 10;
		bulletPower = 400.0f;
		for (int i = 0; i < bulletNum; i++) {
			bulletCyliner.push_back(new ASRBullet(L"Convict_Gun1_Bullet.png", this));
		}
	}
	else if (_wstr == L"Convict_Gun2.png") {
		type = GunType::GUIDE;
		this->scale.x = this->imageSize.x * 1.5f;
		this->scale.y = this->imageSize.y * 1.5f;
		this->SetParentT(*_player);
		this->SetLocalPosX(-_player->scale.x * 0.4f);
		this->SetLocalPosY(_player->scale.y * 0.5f);
		this->pivot = OFFSET_LB;
		bulletNum = 3;
		bulletPower = 400.0f;
		for (int i = 0; i < bulletNum; i++) {
			bulletCyliner.push_back(new ASRBullet(L"Convict_Gun2_Bullet.png", this));
		}
	}
}

ASRGun::~ASRGun()
{
	for (auto it = bulletCyliner.begin(); it != bulletCyliner.end(); it++) delete (*it);
}

void ASRGun::Update()
{
	for (int i = 0; i < bulletNum; i++) bulletCyliner[i]->Update();
	ObImage::Update();
}

void ASRGun::Render()
{
	for (int i = 0; i < bulletNum; i++) bulletCyliner[i]->Render();
	ObImage::Render();
}

void ASRGun::FireBullet()
{
	for (int i = 0; i < bulletNum; i++) {
		if (not bulletCyliner[i]->GetIsFire()) {
			bulletCyliner[i]->Fire(this, bulletPower);
			break;
		}
	}
}
