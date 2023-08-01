#include "common.h"

BulletMinion::BulletMinion(wstring _wstr,
    GameObject* _shooter, 
    float _power, 
    wstring _deathImg) : ASRBullet(_wstr, _shooter, _power, _deathImg)
{
    distance = 500.0f;
    deathImg->scale.x = deathImg->imageSize.x / 8.0f * resizeScale;
    deathImg->scale.y = deathImg->imageSize.y * resizeScale;
    deathImg->maxFrame.x = 8.0f;
}

BulletMinion::~BulletMinion()
{
}

void BulletMinion::Update()
{
    ASRBullet::Update();
}

void BulletMinion::Render()
{
    ASRBullet::Render();
}
