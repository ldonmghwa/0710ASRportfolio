#include "common.h"

ASRGuided::ASRGuided(wstring _wstr, Vector2 _destPos) : ASRBullet(_wstr)
{
    distance = 600.0f;
    destPos = _destPos;
}

ASRGuided::~ASRGuided()
{
}

void ASRGuided::Update()
{
    if (not isFire) return;

    Vector2 velocity = (destPos - col->GetWorldPos()) * fireDir;
    col->MoveWorldPos(velocity * DELTA);
    col->rotation.z = atan2f(velocity.y, velocity.x);

    col->Update();
    img->Update();
    if ((col->GetWorldPos() - sourcePos).Length() > distance) isFire = false;
}

void ASRGuided::Render()
{
    if (not isFire) return;
    col->Render();
    img->Render();
}
