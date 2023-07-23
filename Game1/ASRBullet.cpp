#include "stdafx.h"
#include "GUIStruct.h"
#include "ASRGun.h"
#include "ASRBullet.h"

ASRBullet::ASRBullet(wstring _wstr, ASRGun* _gun) : ObImage(_wstr)
{
    bulletName = _wstr;
	this->scale.x = this->imageSize.x * 0.5f;
	this->scale.y = this->imageSize.y * 0.5f;
	this->SetParentRT(*_gun);
}

ASRBullet::~ASRBullet()
{
}

void ASRBullet::Fire(GameObject* shooter, float pressPower)
{
    lifeTime = 3.0f;
    scale.x = pressPower * 0.1f;
    scale.y = scale.x * 0.2f;
    isFire = true;
    SetWorldPos(shooter->GetWorldPos());

    this->pressPower = pressPower;
    fireDir = shooter->GetRight();
}

void ASRBullet::Fire(Vector2 pos, Vector2 dir, float pressPower)
{
    lifeTime = 3.0f;
    scale.x = 20;
    scale.y = 5;
    this->pressPower = pressPower;
    isFire = true;
    SetWorldPos(pos);
    //fireDir = shooter->GetRight();
    rotation.z = atan2f(dir.y, dir.x);
}

void ASRBullet::Update()
{
    if (not isFire) return;

    Vector2 velocity = (fireDir * pressPower);
    MoveWorldPos(velocity * DELTA);
    rotation.z = atan2f(velocity.y, velocity.x);

    ObImage::Update();

    lifeTime -= DELTA;
    if (lifeTime <= 0.0f)
    {
        isFire = false;
    }
}

void ASRBullet::Render()
{
    if (not isFire) return;
    ObImage::Render();
}
