#include "common.h"

GunGuided::GunGuided(wstring _wstr,
	Character* _player,
	vector<Character*> _target,
	GunType _type)
	: ASRGun(_wstr, _player, _target, _type)
{
	isClbarAvailable = true;
	bulletNum = 3;

	aimingTime = 3.0f;
	backUpAimingTime = aimingTime;
	curBulletNum = bulletNum;
	curCLIdx = curBulletNum - 1;

	bulletPower = 70.0f;
	backUpReloadTime = 3.0f;
	reloadTime = backUpReloadTime;
	reloadPerSec = (reloadTime - 0.1f) / bulletNum;
	backUpReloadPerSec = reloadPerSec;

	crossLineX = new ObRect();
	crossLineX->scale.x = 50.0f;
	crossLineX->scale.y = 10.0f;
	crossLineX->color = Color(0.5f, 0.1f, 0.0f, 0.5f);
	crossLineY = new ObRect();
	crossLineY->scale.x = 10.0f;
	crossLineY->scale.y = 50.0f;
	crossLineY->color = Color(0.0f, 0.1f, 0.5f, 0.5f);

	cylinderBarTP[0] = new ObImage(L"CylinderUp.png");
	cylinderBarTP[1] = new ObImage(L"CylinderDown.png");
	for (int i = 0; i < 2; i++) {
		cylinderBarTP[i]->scale.x = cylinderBarTP[i]->imageSize.x;
		cylinderBarTP[i]->scale.y = cylinderBarTP[i]->imageSize.y;
	}

	for (int i = 0; i < bulletNum; i++) clbarList.push_back(new CLBar());
	shotSDKey = "PlayerGun2Shot";
	reloadSDKey = "PlayerGun2Reload";
	SOUND->AddSound("bigshotgun_shot_01.wav", shotSDKey);
	SOUND->AddSound("bigshotgun_reload_01.wav", reloadSDKey);
}

GunGuided::~GunGuided()
{
	delete crossLineX;
	delete crossLineY;
	TEXTURE->DeleteTexture(L"Convict_Gun2_Bullet_Death.png");
	SOUND->DeleteSound(shotSDKey);
	SOUND->DeleteSound(reloadSDKey);
}

void GunGuided::Update()
{
	if (isAiming) {
		aimingTime -= DELTA;
		LIGHT->screenPos = INPUT->GetScreenMousePos();
		LIGHT->radius = 100.0f;
		LIGHT->outColor = Color(0.1f, 0.2f, 0.3f, 0.1f);
		crossLineX->SetWorldPos(INPUT->GetWorldMousePos());
		crossLineY->SetWorldPos(INPUT->GetWorldMousePos());
		crossLineX->Update();
		crossLineY->Update();
		if (INPUT->KeyDown(VK_LBUTTON)) {
			for (int i = 0; i < target.size(); i++) {
				if (target[i]->GetCol()->Intersect(INPUT->GetWorldMousePos())) {
					this->FireBullet(target[i]);
					isAiming = false;
					aimingTime = backUpAimingTime;
					LIGHT->radius = 10000.0f;
					LIGHT->screenPos = Vector2(0, 0);
					break;
				}
			}
		}
		if (aimingTime < 0) {
			isAiming = false;
			aimingTime = backUpAimingTime;
			LIGHT->radius = 10000.0f;
			LIGHT->screenPos = Vector2(0, 0);
		}
	}
	ASRGun::Update();
}

void GunGuided::Render()
{
	if (isAiming) {
		crossLineX->Render();
		crossLineY->Render();
	}
	ASRGun::Render();
}

void GunGuided::FireBullet()
{
	isAiming = not isAiming;
	aimingTime = backUpAimingTime;
	LIGHT->radius = 10000.0f;
	LIGHT->screenPos = Vector2(0, 0);
}

void GunGuided::FireBullet(Character* _target)
{
	if (isCylinderEmpty) return;
	if (!isAiming) return;
	bulletCylinder.push_back(
		new BulletGuided(L"Convict_Gun2_Bullet.png",
			_target,
			this->col, 
			bulletPower,
			L"Convict_Gun2_Bullet_Death.png")
	);
	ASRGun::FireBullet();
}
