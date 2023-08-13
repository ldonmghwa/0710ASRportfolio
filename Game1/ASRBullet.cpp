#include "common.h"

ASRBullet::ASRBullet(wstring _wstr, 
    GameObject* _shooter,
    float _power, 
    wstring _deathImg) 
    : Item()
{
    isFire = true;
    isHitting = false;
    damagePoint = 1;
    pressPower = _power;
    backUpPressPower = pressPower;
    resizeScale = 2.0f;
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
    col->isVisible = false;
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
    if (isHitting) 
        deathImg->Update();
    if (isVisible) {
        if (not isFire) return;
        Vector2 velocity = (fireDir * pressPower);
        col->MoveWorldPos(velocity * DELTA);
        col->rotation.z = atan2f(velocity.y, velocity.x);
        Item::Update();
        img->Update();
    }
}

void ASRBullet::Render()
{
    if (isHitting)
        deathImg->Render();
    if (isVisible) {
        if (not isFire) return;
        Item::Render();
        img->Render();
    }
}
void ASRBullet::Fire()
{
    pressPower = backUpPressPower;
    isFire = true;
}
void ASRBullet::Render(Camera* uicam)
{
    if (isVisible) {
        if (isHitting) deathImg->Render();
        if (not isFire) return;
        Item::Render(uicam);
        img->Render(uicam);
    }
}
bool ASRBullet::IsBulletReach()
{
    if ((col->GetWorldPos() - sourcePos).Length() > distance) {
        isFire = false;
        deathImg->ChangeAnim(ANIMSTATE::STOP, 0.1f);
        return false;
    }
    else return true;
}

void ASRBullet::IsBulletReach(ObTileMap* _tileMap)
{
    Int2 bulletIdx;
    if (_tileMap->WorldPosToTileIdx(this->col->GetWorldPos(), bulletIdx)) {
        if (_tileMap->GetTileState(bulletIdx) == TILE_WALL) {
            isHitting = true;
            this->isVisible = false;
        }
    }
}

void ASRBullet::IsBulletReach(vector<Character*> target)
{
    for (int i = 0; i < target.size(); i++) {
        if (target[i]->isInvincible) continue;
        if (target[i]->healPoint <= 0) continue;
        if (col->Intersect(target[i]->GetCol()) && !isHitting) {        
            target[i]->TakeDamage(this->damagePoint);
            target[i]->isGlitStart = true;
            this->isVisible = false;
            isHitting = true;
        }
    }
}
