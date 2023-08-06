#include "common.h"

BulletBoss::BulletBoss(wstring _wstr,
	GameObject* _shooter,
	float _power,
	wstring _deathImg,
	float _resizeScale,
	BossScene _type) : ASRBullet(_wstr, _shooter, _power, _deathImg)
{
	isTimeOut = false;
	isFire = false;
	distance = 100000.0f;
	bulletLifeTime = 12.0f;
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

void BulletBoss::Render()
{
	ASRBullet::Render();
}

void BulletBoss::Fire()
{
	pressPower = backUpPressPower;
	isFire = true;
}
