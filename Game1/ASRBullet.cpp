#include "common.h"

ASRBullet::ASRBullet(wstring _wstr, 
    GameObject* _shooter, float _power) 
    : Item()
{
    isFire = true;
    isBulletDeath = false;
    pressPower = _power;
    resizeScale = 1.5f;
    sourcePos = _shooter->GetWorldPos();
    fireDir = _shooter->GetRight();
    type = ItemType::CONSUM;
    img = new ObImage(_wstr);
    img->scale.x = img->imageSize.x * resizeScale;
    img->scale.y = img->imageSize.y * resizeScale;
    col->scale = img->scale;
    col->isFilled = false;
    col->SetWorldPos(_shooter->GetWorldPos());
    img->SetParentRT(*col);
    col->Update();
    distance = 500.0f;
}

ASRBullet::~ASRBullet()
{
    delete bulletDeath;
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
    if (isBulletDeath) {
        bulletDeath->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
        bulletDeath->Update();
    }
}

void ASRBullet::Render()
{
    if (not isFire) return;
    col->Render();
    img->Render();
    if (isBulletDeath) bulletDeath->Render();
}

void ASRBullet::SetBulletDeathImg(wstring _fileName)
{
    bulletDeath = new ObImage(_fileName);
    bulletDeath->scale.x = bulletDeath->imageSize.x * resizeScale;
    bulletDeath->scale.y = bulletDeath->imageSize.y * resizeScale;
    bulletDeath->SetParentRT(*col);
}

bool ASRBullet::IsBulletReach()
{
    if ((col->GetWorldPos() - sourcePos).Length() > distance) {
        isFire = false;
        return false;
    }
    else return true;
}

void ASRBullet::IsBulletReach(vector<Character*> target)
{
    for (int i = 0; i < target.size(); i++) {
        if (target[i]->isInvincible) return;
        if (target[i]->healPoint <= 0) return;
        if (col->Intersect(target[i]->GetCol())) {
            target[i]->TakeDamage();
            isFire = false;
        }
    }
}
