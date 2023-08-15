#include "common.h"

BulletBossRotateGuide::BulletBossRotateGuide(wstring _wstr,
	Character* _target, 
	GameObject* _shooter, 
	float _power,
	wstring _deathImg) : BulletGuided(_wstr, _target, _shooter, _power, _deathImg)
{
    bulletLifeTime = 15.0f;
    backUpBulletLifeTime = bulletLifeTime;
    damagePoint = 1;
	rotateTime = 5.0f;
	backUpRotateTime = rotateTime * 2.0f;
	stopTime = 2.0f;
    img->scale.x = img->imageSize.x * resizeScale;
    img->scale.y = img->imageSize.y * resizeScale;
    col->scale = img->scale;
    deathImg->scale.x = deathImg->imageSize.x / 11.0f * resizeScale;
    deathImg->scale.y = deathImg->imageSize.y * resizeScale;
    deathImg->maxFrame.x = 11;
	dis = 0.0f;
	for (int i = 0; i < 3; i++) isRotate[i] = false;
	isRotate[0] = true;
}

BulletBossRotateGuide::~BulletBossRotateGuide()
{
}

void BulletBossRotateGuide::Update()
{
	if (isHitting)
		deathImg->Update();
	if (isVisible) {
		if (not isFire) return;
		if (isRotate[0]) {
			rotateTime -= DELTA;
			col->rotation2.z -= 2.0f * DELTA;
			dis += 20.0f * DELTA;
			col->SetLocalPosX(dis);
			col->SetLocalPosY(dis);
			if (rotateTime < 0) {
				img->color.y = 1.0f;
				isRotate[0] = false;
				isRotate[1] = true;
			}
		}
		else if (isRotate[1]) {
			stopTime -= DELTA;
			if (stopTime < 0) {
				targetLastPos = target->GetCol()->GetWorldPos();
				col->rotation2.z = 0.0f;
				img->color.y = 0.5f;
				img->color.x = 1.0f;
				pressPower = 500.0f;
				isRotate[1] = false;
				isRotate[2] = true;
				col->SetWorldPos(Vector2(col->GetWorldPos().x, col->GetWorldPos().y));
				sourcePos = col->GetWorldPos();
			}	
		}
		else if(isRotate[2]){
			Vector2 velocity1 = (targetLastPos - sourcePos);
			velocity1.Normalize();
			Vector2 velocity = velocity1 * pressPower;
			col->MoveWorldPos(velocity * DELTA);
			//col->rotation.z = atan2f(velocity.y, velocity.x);
		}
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

void BulletBossRotateGuide::Render()
{
	BulletGuided::Render();
}
