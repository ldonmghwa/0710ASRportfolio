#include "common.h"

BulletBossGuided::BulletBossGuided(wstring _wstr, 
    Character* _target, 
    GameObject* _shooter,
    float _power, 
    wstring _deathImg) : BulletGuided(_wstr, _target, _shooter, _power, _deathImg)
{
    bulletLifeTime = 10;
    backUpBulletLifeTime = bulletLifeTime;
    damagePoint = 1;
    img->scale.x = img->imageSize.x / 8.0f * resizeScale;
    img->scale.y = img->imageSize.y * resizeScale;
    img->maxFrame.x = 8;
    img->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
    col->scale = img->scale;
    deathImg->scale.x = deathImg->imageSize.x / 8.0f * resizeScale;
    deathImg->scale.y = deathImg->imageSize.y * resizeScale;
    deathImg->maxFrame.x = 8;
}

BulletBossGuided::~BulletBossGuided()
{
}

void BulletBossGuided::Update()
{
    bulletLifeTime -= DELTA;
    BulletGuided::Update();
    if (bulletLifeTime < 0) {
        isFire = false;
        bulletLifeTime = backUpBulletLifeTime;
    }
}

void BulletBossGuided::Render()
{
    BulletGuided::Render();
}
