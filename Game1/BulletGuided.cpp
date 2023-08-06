#include "common.h"

BulletGuided::BulletGuided(wstring _wstr,
    Character* _target,
    GameObject* _shooter,
    float _power,
    wstring _deathImg) : ASRBullet(_wstr, _shooter, _power, _deathImg)
{
    damagePoint = 3;
    distance = 10000.0f;
    target = _target;
    deathImg->scale.x = deathImg->imageSize.x / 12.0f * resizeScale;
    deathImg->scale.y = deathImg->imageSize.y * resizeScale;
    deathImg->maxFrame.x = 12.0f;
}

BulletGuided::~BulletGuided()
{
}

void BulletGuided::Update()
{
    
    if (isVisible) {
        if (isHitting) deathImg->Update();
        if (not isFire) return;
        Vector2 velocity1 = (target->GetCol()->GetWorldPos() - col->GetWorldPos());
        velocity1.Normalize();
        Vector2 velocity = velocity1 * pressPower;
        col->MoveWorldPos(velocity * DELTA);
        col->rotation.z = atan2f(velocity.y, velocity.x);

        col->Update();
        img->Update();
    }
}

void BulletGuided::Render()
{
    ASRBullet::Render();
}
