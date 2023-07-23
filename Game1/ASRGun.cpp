#include "stdafx.h"
#include "GUIStruct.h"
#include "Player.h"
#include "ASRBullet.h"
#include "ASRGun.h"

ASRGun::ASRGun(wstring _wstr, Player* _player): ObImage(_wstr)
{
	if (_wstr == L"Convict_Gun1.png") {
		type = GunType::BASIC;
		this->scale.x = this->imageSize.x;
		this->scale.y = this->imageSize.y;
		this->SetParentRT(*_player);
		this->SetLocalPos(Vector2(-_player->scale.x * 0.5f, -_player->scale.y * 0.2f));
		bulletNum = 10;
		for (int i = 0; i < bulletNum; i++) {
			bulletCyliner.push_back(new ASRBullet(L"Convict_Gun1_Bullet.png", this));
		}
	}
}

ASRGun::~ASRGun()
{
	for (auto it = bulletCyliner.begin(); it != bulletCyliner.end(); it++) delete (*it);
	TEXTURE->DeleteTexture(L"Convict_Gun1.png");
	TEXTURE->DeleteTexture(L"Convict_Gun1_Bullet.png");
	TEXTURE->DeleteTexture(L"Convict_Gun1_Bullet_Death.png");
}

void ASRGun::Update()
{
	ObImage::Update();
}

void ASRGun::Render()
{
	ObImage::Render();
}
