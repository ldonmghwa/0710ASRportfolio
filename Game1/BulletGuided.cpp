#include "common.h"

BulletGuided::BulletGuided(wstring _wstr,
    Vector2 _destPos,
    GameObject* _shooter,
    float _power,
    wstring _deathImg) : ASRBullet(_wstr, _shooter, _power, _deathImg)
{
    distance = 600.0f;
    destPos = _destPos;
    deathImg->scale.x = deathImg->imageSize.x / 12.0f * resizeScale;
    deathImg->scale.y = deathImg->imageSize.y * resizeScale;
    deathImg->maxFrame.x = 12.0f;
}

BulletGuided::~BulletGuided()
{
}

void BulletGuided::Update()
{
    if (not isFire) return;

    Vector2 velocity = (destPos - col->GetWorldPos()) * fireDir;
    col->MoveWorldPos(velocity * DELTA);
    col->rotation.z = atan2f(velocity.y, velocity.x);

    col->Update();
    img->Update();
    if ((col->GetWorldPos() - sourcePos).Length() > distance) isFire = false;
}

void BulletGuided::Render()
{
    ASRBullet::Render();
}
