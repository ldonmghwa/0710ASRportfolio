#include "common.h"

ASRBullet::ASRBullet(wstring _wstr, 
    GameObject* _shooter,
    float _power, 
    wstring _deathImg) 
    : Item()
{
    isFire = true;
    isHitting = false;
    isRending = false;
    pressPower = _power;
    resizeScale = 1.5f;
    sourcePos = _shooter->GetWorldPos();
    fireDir = _shooter->GetRight();
    type = ItemType::CONSUM;

    img = new ObImage(_wstr);
    img->scale.x = img->imageSize.x * resizeScale;
    img->scale.y = img->imageSize.y * resizeScale;

    deathImg = new ObImage(_deathImg);
    deathImg->scale.x = deathImg->imageSize.x / 5.0f * resizeScale;
    deathImg->scale.y = deathImg->imageSize.y * resizeScale;
    deathImg->maxFrame.x = 5.0f;
    deathImg->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

    col->scale = img->scale;
    col->isFilled = false;
    col->SetWorldPos(_shooter->GetWorldPos());
    img->SetParentRT(*col);
    deathImg->SetParentRT(*col);
    col->Update();
    distance = 500.0f;
}

ASRBullet::~ASRBullet()
{
    delete deathImg;
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
    if (isHitting) deathImg->Update();
    if (not isFire) return;
    Vector2 velocity = (fireDir * pressPower);
    col->MoveWorldPos(velocity * DELTA);
    col->rotation.z = atan2f(velocity.y, velocity.x);
    Item::Update();
    img->Update();
    
}

void ASRBullet::Render()
{
    if (isHitting) deathImg->Render();
    if (not isFire) return;
    Item::Render();
    img->Render();
    
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
        if (target[i]->isInvincible) continue;
        if (target[i]->healPoint <= 0) continue;
        if (col->Intersect(target[i]->GetCol()) && !isHitting) {        
            target[i]->TakeDamage();
            isHitting = true;
            isFire = false;
        }
    }
}
