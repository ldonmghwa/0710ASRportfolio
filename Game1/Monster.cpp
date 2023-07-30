#include "common.h"

Monster::Monster() : Character()
{
    monsterType = MTType::MTMINION;
    resizeValue = 2.5f;
    charImg[(int)CRState::IDLE] = new ObImage(L"BulletKin_Idle.png");
    charImg[(int)CRState::IDLE]->maxFrame.x = 2;
    charImg[(int)CRState::IDLE]->maxFrame.y = 3;
    charImg[(int)CRState::IDLE]->scale.x = charImg[(int)CRState::IDLE]->imageSize.x / 2.0f * resizeValue;
    charImg[(int)CRState::IDLE]->scale.y = charImg[(int)CRState::IDLE]->imageSize.y / 3.0f * resizeValue;
    charImg[(int)CRState::IDLE]->pivot = OFFSET_B;
    charImg[(int)CRState::IDLE]->SetParentRT(*col);

    charImg[(int)CRState::WALK] = new ObImage(L"BulletKin_Walk.png");
    charImg[(int)CRState::WALK]->maxFrame.x = 6;
    charImg[(int)CRState::WALK]->maxFrame.y = 3;
    charImg[(int)CRState::WALK]->scale.x = charImg[(int)CRState::WALK]->imageSize.x / 6.0f * resizeValue;
    charImg[(int)CRState::WALK]->scale.y = charImg[(int)CRState::WALK]->imageSize.y / 3.0f * resizeValue;
    charImg[(int)CRState::WALK]->pivot = OFFSET_B;
    charImg[(int)CRState::WALK]->SetParentRT(*col);

    charImg[(int)CRState::HIT] = new ObImage(L"BulletKin_Hit.png");
    charImg[(int)CRState::HIT]->maxFrame.x = 13;
    charImg[(int)CRState::HIT]->scale.x = charImg[(int)CRState::HIT]->imageSize.x / 13.0f * resizeValue;
    charImg[(int)CRState::HIT]->scale.y = charImg[(int)CRState::HIT]->imageSize.y * resizeValue;
    charImg[(int)CRState::HIT]->pivot = OFFSET_B;
    charImg[(int)CRState::HIT]->SetParentRT(*col);

    charImg[(int)CRState::DEATH] = new ObImage(L"BulletKin_Death.png");
    charImg[(int)CRState::DEATH]->maxFrame.x = 5;
    charImg[(int)CRState::DEATH]->scale.x = charImg[(int)CRState::DEATH]->imageSize.x / 5.0f * resizeValue;
    charImg[(int)CRState::DEATH]->scale.y = charImg[(int)CRState::DEATH]->imageSize.y * resizeValue;
    charImg[(int)CRState::DEATH]->pivot = OFFSET_B;
    charImg[(int)CRState::DEATH]->SetParentRT(*col);

    
    col->scale.x = charImg[(int)CRState::IDLE]->scale.x;
    col->scale.y = charImg[(int)CRState::IDLE]->scale.y;
    col->pivot = OFFSET_B;
    col->isFilled = false;

    dirFrame[0] = 1;
    dirFrame[1] = 1;
    dirFrame[2] = 0;
    dirFrame[3] = 1;
    dirFrame[4] = 1;
    dirFrame[5] = 2;
    dirFrame[6] = 2;
    dirFrame[7] = 2;
}

Monster::~Monster()
{
    TEXTURE->DeleteTexture(L"BulletKin_Idle.png");
    TEXTURE->DeleteTexture(L"BulletKin_Walk.png");
    TEXTURE->DeleteTexture(L"BulletKin_Hit.png");
    TEXTURE->DeleteTexture(L"BulletKin_Death.png");
}

void Monster::Init(Vector2 spawn)
{
    gun = new GunMinion(L"BulletKin_Gun.png", col, target, GunType::MINION);
    Character::Init(spawn);
    speed = 25.0f;
    attackRange = 400.0f;
    detectionRange = 600.0f; 
    shootingInterval = 2.0f;
}

void Monster::Control()
{
}

void Monster::Update()
{
    lastPos = col->GetWorldPos();
    gun->Update();
    Character::Update();
    if (gun->GetIsCylinderEmpty()) {
        gun->GunReLoading();
    }
    if (state == CRState::IDLE)
    {
        LookTarget(target[0]->GetWorldPos());
        if((col->GetWorldPos() - target[0]->GetWorldPos()).Length() < detectionRange) {
            shootingInterval = 2.0f;
            state = CRState::WALK;
            charImg[(int)CRState::WALK]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
    }
    else if (state == CRState::WALK)
    {
        shootingInterval -= DELTA;
        LookTarget(target[0]->GetWorldPos());
        Vector2 moveDir = target[0]->GetWorldPos() - col->GetWorldPos();
        moveDir.Normalize();
        col->MoveWorldPos(moveDir * speed * DELTA);
        if ((col->GetWorldPos() - target[0]->GetWorldPos()).Length() >= detectionRange) {
            state = CRState::IDLE;
            charImg[(int)CRState::IDLE]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if ((col->GetWorldPos() - target[0]->GetWorldPos()).Length() < attackRange) {
            if (shootingInterval < 0) {
                shootingInterval = 2.0f;
                gun->FireBullet();
            }
        }
        if (gun->isReloading) {
            state = CRState::IDLE;
            charImg[(int)CRState::IDLE]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
    }
}

void Monster::Render()
{
    Character::Render();
    gun->Render();
}

void Monster::GoBack()
{
    Character::GoBack();
}

void Monster::LookTarget(Vector2 target)
{
    Character::LookTarget(target);
    if (state != CRState::DEATH or state != CRState::HIT) charImg[(int)state]->frame.y = dirFrame[index];
    if (index == 0 or index == 1) {
        gun->GetCol()->rotation.z = -atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
        gun->GetCol()->SetLocalPosX(-col->scale.x * 0.3f);
        gun->GetCol()->SetLocalPosY(col->scale.y * 0.25f);
        //gunVector[selectWPNum]->rotation.y = PI;
        gun->GetCol()->rotation.x = PI;
        charImg[(int)state]->rotation.y = 0.0f;
    }
    else {
        gun->GetCol()->rotation.z = atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
        gun->GetCol()->SetLocalPosX(col->scale.x * 0.3f);
        gun->GetCol()->SetLocalPosY(col->scale.y * 0.25f);
        gun->GetCol()->rotation.y = 0.0f;
        gun->GetCol()->rotation.x = 0.0f;
        charImg[(int)state]->rotation.y = PI;
    }

}
