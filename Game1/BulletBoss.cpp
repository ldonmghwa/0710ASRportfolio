#include "common.h"

BulletBoss::BulletBoss(wstring _wstr,
	GameObject* _shooter,
	float _power,
	wstring _deathImg,
	float _resizeScale,
	BossScene _type,
	float _dis) : ASRBullet(_wstr, _shooter, _power, _deathImg)
{
	isTimeOut = false;
	isFire = false;
	dis = _dis;
	distance = 100000.0f;
	bulletLifeTime = 15.0f;
	backUpBulletLifeTime = bulletLifeTime;
	img->scale.x = img->imageSize.x * resizeScale * _resizeScale;
	img->scale.y = img->imageSize.y * resizeScale * _resizeScale;
	col->scale = img->scale;
	deathImg->scale.x = deathImg->imageSize.x / 11.0f * resizeScale * _resizeScale * 0.5f;
	deathImg->scale.y = deathImg->imageSize.y * resizeScale * _resizeScale * 0.5f;
	deathImg->maxFrame.x = 11.0f;
	pressPower = 0;
	if (_type == BossScene::BASIC) fireDir = _shooter->GetRight();
	else if (_type == BossScene::MAZE) fireDir = DOWN;
}

BulletBoss::~BulletBoss()
{
}

void BulletBoss::Update()
{
	ASRBullet::Update();
	bulletLifeTime -= DELTA;
	if (bulletLifeTime <= 0.0f) {
		isTimeOut = true;
		isFire = false;
		bulletLifeTime = backUpBulletLifeTime;
	}
}

void BulletBoss::Update(float _dis)
{
	if (isHitting)
		deathImg->Update();
	if (isVisible) {
		if (not isFire) return;
		dis += _dis;
		col->SetLocalPosY(dis);
		col->rotation2.z += DELTA * 5.0f;
		Item::Update();
		img->Update();
	}
	bulletLifeTime -= DELTA;
	if (bulletLifeTime <= 0.0f) {
		isTimeOut = true;
		isFire = false;
		bulletLifeTime = backUpBulletLifeTime;
	}
}

void BulletBoss::Render()
{
	ASRBullet::Render();
}
