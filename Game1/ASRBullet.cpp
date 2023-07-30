#include "common.h"

ASRBullet::ASRBullet(wstring _wstr, GameObject* _shooter, float _power) 
    : Item()
{
    isFire = true;
    pressPower = _power;
    sourcePos = _shooter->GetWorldPos();
    fireDir = _shooter->GetRight();
    type = ItemType::CONSUM;
    img = new ObImage(_wstr);
    img->scale.x = img->imageSize.x * 1.5f;
    img->scale.y = img->imageSize.y * 1.5f;
    col->scale = img->scale;
    col->isFilled = false;
    col->SetWorldPos(_shooter->GetWorldPos());
    img->SetParentRT(*col);
    col->Update();
    //col->SetWorldPos(Vector2(-1250.0f , -1250.0f));
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
    if ((col->GetWorldPos() - sourcePos).Length() > distance) {
        isFire = false;
        return false;
    }
    else return true;
}

bool ASRBullet::IsBulletReach(vector<GameObject*> target)
{
    for (int i = 0; i < target.size(); i++) {
        if (col->Intersect(target[i])) {
            isFire = false;
            return false;
        }
        else return true;
    }
}
