#include "common.h"

ASRBullet::ASRBullet(wstring _wstr)
{
    type = ItemType::CONSUM;
    img = new ObImage(_wstr);
    img->scale.x = img->imageSize.x * 1.5f;
    img->scale.y = img->imageSize.y * 1.5f;
    col->scale = img->scale;
    col->isFilled = false;
    img->SetParentRT(*col);
    distance = 500.0f;

}

ASRBullet::~ASRBullet()
{
}

void ASRBullet::Fire(GameObject* shooter, float pressPower)
{
    this->pressPower = pressPower;
    isFire = true;
    sourcePos = shooter->GetWorldPos();
    col->SetWorldPos(shooter->GetWorldPos());
    fireDir = shooter->GetRight();
}

void ASRBullet::Fire(Vector2 sourPos, Vector2 dir, float pressPower)
{
    this->pressPower = pressPower;
    isFire = true;
    sourcePos = sourPos;
    col->SetWorldPos(sourPos);
    col->rotation.z = atan2f(dir.y, dir.x);
}

void ASRBullet::Update()
{
    if (not isFire) return;

    Vector2 velocity = (fireDir * pressPower);
    col->MoveWorldPos(velocity * DELTA);
    col->rotation.z = atan2f(velocity.y, velocity.x);

    col->Update();
    img->Update();
    
}

void ASRBullet::Render()
{
    if (not isFire) return;
    col->Render();
    img->Render();
}

bool ASRBullet::IsBulletReach()
{
    if ((col->GetWorldPos() - sourcePos).Length() > distance) isFire = false;
}
