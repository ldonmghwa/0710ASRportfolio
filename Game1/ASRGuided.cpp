#include "common.h"

ASRGuided::ASRGuided(wstring _wstr) : ASRBullet(_wstr)
{
    distance = 600.0f;
}

ASRGuided::~ASRGuided()
{
}

void ASRGuided::Update(Vector2 destPos)
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
    col->Render();
    img->Render();
}
