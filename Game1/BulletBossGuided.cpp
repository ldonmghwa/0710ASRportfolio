#include "common.h"

BulletBossGuided::BulletBossGuided(wstring _wstr, 
    Character* _target, 
    GameObject* _shooter,
    float _power, 
    wstring _deathImg) : BulletGuided(_wstr, _target, _shooter, _power, _deathImg)
{
    lifeTime = 5.0f;
    backUpLifeTime = lifeTime;
    damagePoint = 5;
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
    lifeTime -= DELTA;
    BulletGuided::Update();
    if (lifeTime < 0) {
        isFire = false;
        lifeTime = backUpLifeTime;
    }
}

void BulletBossGuided::Render()
{
    BulletGuided::Render();
}
