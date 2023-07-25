#include "stdafx.h"
#include "GUIStruct.h"
#include "ASRGun.h"
#include "ASRBullet.h"

ASRBullet::ASRBullet(wstring _wstr, ASRGun* _gun) : ObImage(_wstr)
{
    bulletName = _wstr;
    this->scale.x = this->imageSize.x * 2.0f;
    this->scale.y = this->imageSize.y * 2.0f;
    distance = 500.0f;
    //this->SetParentT(*_gun);
}

ASRBullet::~ASRBullet()
{
}

void ASRBullet::Fire(GameObject* shooter, float pressPower)
{
    this->pressPower = pressPower;
    isFire = true;
    sourcePos = shooter->GetWorldPos();
    SetWorldPos(shooter->GetWorldPos());
    fireDir = shooter->GetRight();
}

void ASRBullet::Fire(Vector2 sourPos, Vector2 dir, float pressPower)
{
    this->pressPower = pressPower;
    isFire = true;
    sourcePos = sourPos;
    SetWorldPos(sourPos);
    rotation.z = atan2f(dir.y, dir.x);
}

void ASRBullet::Update()
{
    if (not isFire) return;

    Vector2 velocity = (fireDir * pressPower);
    MoveWorldPos(velocity * DELTA);
    rotation.z = atan2f(velocity.y, velocity.x);

    ObImage::Update();
    if ((this->GetWorldPos() - sourcePos).Length() > distance) isFire = false;

}

void ASRBullet::Render()
{
    if (not isFire) return;
    ObImage::Render();
}
