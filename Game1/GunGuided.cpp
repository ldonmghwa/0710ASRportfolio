#include "common.h"

GunGuided::GunGuided(wstring _wstr,
	Character* _player,
	vector<Character*> _target,
	GunType _type)
	: ASRGun(_wstr, _player, _target, _type)
{
	bulletNum = 3;
	curBulletNum = bulletNum;
	bulletPower = 600.0f;
	backUpReloadTime = 3.0f;
	reloadTime = 3.0f;
	crossLineX = new ObLine();
	crossLineX->scale.x = 20.0f;
	crossLineX->scale.y = 5.0f;
	crossLineY = new ObLine();
	crossLineY->scale.x = 5.0f;
	crossLineY->scale.y = 20.0f;
}

GunGuided::~GunGuided()
{
	TEXTURE->DeleteTexture(L"Convict_Gun2_Bullet_Death.png");
}

void GunGuided::Update()
{
	crossLineX->SetWorldPos(INPUT->GetWorldMousePos());
	crossLineY->SetWorldPos(INPUT->GetWorldMousePos());
	crossLineX->Update();
	crossLineY->Update();
	ASRGun::Update();
}

void GunGuided::Render()
{
	crossLineX->Render();
	crossLineY->Render();
	ASRGun::Render();
}

void GunGuided::FireBullet(Vector2 _destPos)
{
	if (isCylinderEmpty) return;
	bulletCylinder.push_back(
		new BulletGuided(L"Convict_Gun2_Bullet.png",
			_destPos,
			this->col, 
			bulletPower,
			L"Convict_Gun2_Bullet_Death.png")
	);
	ASRGun::FireBullet();
}
