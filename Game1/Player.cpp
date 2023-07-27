#include "common.h"

Player::Player()
    : Character()
{
        playerType = PLType::PLCONVICT;
        idle = new ObImage(L"Char_Convict_Idle.png");
        idle->maxFrame.x = 4;
        idle->maxFrame.y = 4;
        idle->scale.x = idle->imageSize.x / 4.0f * 3.0f;
        idle->scale.y = idle->imageSize.y / 4.0f * 3.0f;
        idle->pivot = OFFSET_B;
        idle->SetParentRT(*col);

        idleWithWeapon = new ObImage(L"Char_Convict_IdleWithWeapon.png");
        idleWithWeapon->maxFrame.x = 4;
        idleWithWeapon->maxFrame.y = 4;
        idleWithWeapon->scale.x = idleWithWeapon->imageSize.x / 4.0f * 3.0f;
        idleWithWeapon->scale.y = idleWithWeapon->imageSize.y / 4.0f * 3.0f;
        idleWithWeapon->pivot = OFFSET_B;
        idleWithWeapon->SetParentRT(*col);

        walk = new ObImage(L"Char_Convict_Walking.png");
        walk->maxFrame.x = 6;
        walk->maxFrame.y = 4;
        walk->scale.x = walk->imageSize.x / 6.0f * 3.0f;
        walk->scale.y = walk->imageSize.y / 4.0f * 3.0f;
        walk->pivot = OFFSET_B;
        walk->SetParentRT(*col);

        walkWithWeapon = new ObImage(L"Char_Convict_WalkingWithWeapon.png");
        walkWithWeapon->maxFrame.x = 6;
        walkWithWeapon->maxFrame.y = 4;
        walkWithWeapon->scale.x = walkWithWeapon->imageSize.x / 6.0f * 3.0f;
        walkWithWeapon->scale.y = walkWithWeapon->imageSize.y / 4.0f * 3.0f;
        walkWithWeapon->pivot = OFFSET_B;
        walkWithWeapon->SetParentRT(*col);

        dodgeRoll = new ObImage(L"Char_Convict_DodgeRoll.png");
        dodgeRoll->maxFrame.x = 9;
        dodgeRoll->maxFrame.y = 4;
        dodgeRoll->scale.x = dodgeRoll->imageSize.x / 9.0f * 3.0f;
        dodgeRoll->scale.y = dodgeRoll->imageSize.y / 4.0f * 3.0f;
        dodgeRoll->pivot = OFFSET_B;
        dodgeRoll->SetParentRT(*col);

        death = new ObImage(L"Char_Convict_Death1.png");
        death->maxFrame.x = 11;
        death->scale.x = death->imageSize.x / 11.0f * 3.0f;
        death->scale.y = death->imageSize.y * 3.0f;
        death->pivot = OFFSET_B;
        death->SetParentRT(*col);

        col->scale.x = idle->scale.x;
        col->scale.y = idle->scale.y;

        gunVector.push_back(new GunBasic(L"Convict_Gun1.png", col, GunType::BASIC));
        gunVector[0]->VisibleOff();
    col->pivot = OFFSET_B;
    col->isFilled = false;


    dirFrame[0] = 1;
    dirFrame[1] = 1;
    dirFrame[2] = 0;
    dirFrame[3] = 1;
    dirFrame[4] = 1;
    dirFrame[5] = 3;
    dirFrame[6] = 2;
    dirFrame[7] = 3;
}

Player::Player(PLType _type) 
    : Character()
{
    if (_type == PLType::PLCONVICT)
    {
        playerType = _type;
        idle = new ObImage(L"Char_Convict_Idle.png");
        idle->maxFrame.x = 4;
        idle->maxFrame.y = 4;
        idle->scale.x = idle->imageSize.x / 4.0f * 3.0f;
        idle->scale.y = idle->imageSize.y / 4.0f * 3.0f;
        idle->pivot = OFFSET_B;
        idle->SetParentRT(*col);

        idleWithWeapon = new ObImage(L"Char_Convict_IdleWithWeapon.png");
        idleWithWeapon->maxFrame.x = 4;
        idleWithWeapon->maxFrame.y = 4;
        idleWithWeapon->scale.x = idleWithWeapon->imageSize.x / 4.0f * 3.0f;
        idleWithWeapon->scale.y = idleWithWeapon->imageSize.y / 4.0f * 3.0f;
        idleWithWeapon->pivot = OFFSET_B;
        idleWithWeapon->SetParentRT(*col);

        walk = new ObImage(L"Char_Convict_Walking.png");
        walk->maxFrame.x = 6;
        walk->maxFrame.y = 4;
        walk->scale.x = walk->imageSize.x / 6.0f * 3.0f;
        walk->scale.y = walk->imageSize.y / 4.0f * 3.0f;
        walk->pivot = OFFSET_B;
        walk->SetParentRT(*col);

        walkWithWeapon = new ObImage(L"Char_Convict_WalkingWithWeapon.png");
        walkWithWeapon->maxFrame.x = 6;
        walkWithWeapon->maxFrame.y = 4;
        walkWithWeapon->scale.x = walkWithWeapon->imageSize.x / 6.0f * 3.0f;
        walkWithWeapon->scale.y = walkWithWeapon->imageSize.y / 4.0f * 3.0f;
        walkWithWeapon->pivot = OFFSET_B;
        walkWithWeapon->SetParentRT(*col);

        dodgeRoll = new ObImage(L"Char_Convict_DodgeRoll.png");
        dodgeRoll->maxFrame.x = 9;
        dodgeRoll->maxFrame.y = 4;
        dodgeRoll->scale.x = dodgeRoll->imageSize.x / 9.0f * 3.0f;
        dodgeRoll->scale.y = dodgeRoll->imageSize.y / 4.0f * 3.0f;
        dodgeRoll->pivot = OFFSET_B;
        dodgeRoll->SetParentRT(*col);

        death = new ObImage(L"Char_Convict_Death1.png");
        death->maxFrame.x = 11;
        death->scale.x = death->imageSize.x / 11.0f * 3.0f;
        death->scale.y = death->imageSize.y * 3.0f;
        death->pivot = OFFSET_B;
        death->SetParentRT(*col);

        col->scale.x = idle->scale.x;
        col->scale.y = idle->scale.y;

        gunVector.push_back(new GunBasic(L"Convict_Gun1.png", col, GunType::BASIC));
        gunVector[0]->VisibleOff();

    }
    else if (playerType == PLType::PLBULLET) {

    }

    col->pivot = OFFSET_B;
    col->isFilled = false;


    dirFrame[0] = 1;
    dirFrame[1] = 1;
    dirFrame[2] = 0;
    dirFrame[3] = 1;
    dirFrame[4] = 1;
    dirFrame[5] = 3;
    dirFrame[6] = 2;
    dirFrame[7] = 3;
}

Player::~Player()
{
    delete idleWithWeapon;
    delete walkWithWeapon;
    delete dodgeRoll;
    
    for (auto it = gunVector.begin(); it != gunVector.end(); it++) delete (*it);

    TEXTURE->DeleteTexture(L"Char_Convict_Idle.png");
    TEXTURE->DeleteTexture(L"Char_Convict_IdleWithWeapon.png");
    TEXTURE->DeleteTexture(L"Char_Convict_Walking.png");
    TEXTURE->DeleteTexture(L"Char_Convict_WalkingWithWeapon.png");
    TEXTURE->DeleteTexture(L"Char_Convict_DodgeRoll.png");
    TEXTURE->DeleteTexture(L"Char_Convict_Death1.png");
    TEXTURE->DeleteTexture(L"Convict_Gun1.png");
    TEXTURE->DeleteTexture(L"Convict_Gun1_Bullet.png");
    //TEXTURE->DeleteTexture(L"Convict_Gun1_Bullet_Death.png");
    TEXTURE->DeleteTexture(L"Convict_Gun2.png");
    TEXTURE->DeleteTexture(L"Convict_Gun2_Bullet.png");

}

void Player::Init(Vector2 spawn)
{
    col->SetWorldPosX(spawn.x);
    col->SetWorldPosY(spawn.y);
    state = CRState::IDLE;
    speed = 300.0f;
    gunNum = 1;
    isCarryWP = false;
    selectWPNum = 0;
    gunVector[selectWPNum]->VisibleOff();
}

void Player::Control()
{
    controlDir = Vector2();

    //계속 누를때
    if (INPUT->KeyPress('W'))
    {
        controlDir.y = 1.0f;
    }
    else if (INPUT->KeyPress('S'))
    {
        controlDir.y = -1.0f;
    }
    if (INPUT->KeyPress('A'))
    {
        controlDir.x = -1.0f;
    }
    else if (INPUT->KeyPress('D'))
    {
        controlDir.x = 1.0f;
    }
    dir2 = controlDir;
    controlDir.Normalize();

    col->MoveWorldPos(controlDir * DELTA * speed);
}

void Player::Update()
{
    lastPos = col->GetWorldPos();
    CAM->position = col->GetWorldPos();

    if (state == CRState::IDLE)
    {
        LookTarget(INPUT->GetWorldMousePos());

        //idle ->walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = CRState::WALK;
            walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if (INPUT->KeyDown('1')) {
            selectWPNum = '1' - '0' - 1;
            isCarryWP = true;
            gunVector[selectWPNum]->VisibleOn();
            state = CRState::IDLEWP;
            idleWithWeapon->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if (INPUT->KeyDown('2')) {
            if (gunVector.size() >= '2' - '0') {
                selectWPNum = '2' - '0' - 1;
                isCarryWP = true;
                gunVector[selectWPNum]->VisibleOn();
                state = CRState::IDLEWP;
                idleWithWeapon->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
            }
        }
    }
    else if (state == CRState::IDLEWP) {
        LookTarget(INPUT->GetWorldMousePos());

        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = CRState::WALKWP;
            walkWithWeapon->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if (INPUT->KeyDown(VK_LBUTTON)) {
            gunVector[selectWPNum]->FireBullet();
        }
        if (isCarryWP) {
            if (INPUT->KeyDown('1')) {
                if (selectWPNum != '1' - '0' - 1) {
                    gunVector[selectWPNum]->VisibleOff();
                    selectWPNum = '1' - '0' - 1;
                    gunVector[selectWPNum]->VisibleOn();
                }
                else {
                    gunVector[selectWPNum]->VisibleOff();
                    isCarryWP = false;
                    state = CRState::IDLE;
                    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                }
            }
            if (INPUT->KeyDown('2')) {
                if (selectWPNum != '2' - '0' - 1) {
                    gunVector[selectWPNum]->VisibleOff();
                    selectWPNum = '2' - '0' - 1;
                    gunVector[selectWPNum]->VisibleOn();
                }
                else {
                    gunVector[selectWPNum]->VisibleOff();
                    isCarryWP = false;
                    state = CRState::IDLE;
                    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                }
            }
        }
    }
    else if (state == CRState::WALK)
    {
        LookTarget(INPUT->GetWorldMousePos());
        Control();
        //walk->idle
        if (not(INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D')))
        {
            state = CRState::IDLE;
            walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            walk->frame.x = 0;
        }
        //walk->roll
        if (INPUT->KeyDown(VK_RBUTTON))
        {
            beforeDashPoint = col->GetWorldPos();
            state = CRState::ROLL;
            dodgeRoll->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
            rollTime = 0.0f;
        }
        if (INPUT->KeyDown('1')) {
            selectWPNum = '1' - '0' - 1;
            gunVector[selectWPNum]->VisibleOn();
            isCarryWP = true;
            state = CRState::WALKWP;
            walkWithWeapon->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if (INPUT->KeyDown('2')) {
            if (gunVector.size() >= '2' - '0') {
                selectWPNum = '2' - '0' - 1;
                isCarryWP = true;
                gunVector[selectWPNum]->VisibleOn();
                state = CRState::WALKWP;
                walkWithWeapon->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
            }
        }
    }
    else if (state == CRState::WALKWP) {
        LookTarget(INPUT->GetWorldMousePos());
        Control();
        if (not(INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D')))
        {
            if (isCarryWP) state = CRState::IDLEWP;
            else state = CRState::IDLE;
            walkWithWeapon->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            walkWithWeapon->frame.x = 0;
        }
        //walk->roll
        if (INPUT->KeyDown(VK_RBUTTON))
        {
            beforeDashPoint = col->GetWorldPos();
            gunVector[selectWPNum]->VisibleOff();
            state = CRState::ROLL;
            dodgeRoll->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
            rollTime = 0.0f;
        }
        if (INPUT->KeyDown(VK_LBUTTON)) {
            gunVector[selectWPNum]->FireBullet();
        }
        if (isCarryWP) {
            if (INPUT->KeyDown('1')) {
                if (selectWPNum != '1' - '0' - 1) {
                    gunVector[selectWPNum]->VisibleOff();
                    selectWPNum = '1' - '0' - 1;
                    gunVector[selectWPNum]->VisibleOn();
                }
                else {
                    gunVector[selectWPNum]->VisibleOff();
                    isCarryWP = false;
                    state = CRState::WALK;
                    walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                }
            }
            if (INPUT->KeyDown('2')) {
                if (selectWPNum != '2' - '0' - 1) {
                    gunVector[selectWPNum]->VisibleOff();
                    selectWPNum = '2' - '0' - 1;
                    gunVector[selectWPNum]->VisibleOn();
                }
                else {
                    gunVector[selectWPNum]->VisibleOff();
                    isCarryWP = false;
                    state = CRState::WALK;
                    walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                }
            }
        }
    }
    else if (state == CRState::ROLL)
    {
        rollTime += DELTA;
        col->SetWorldPos(Vector2::Lerp(col->GetWorldPos()
            , beforeDashPoint + Vector2(300.0f, 300.0f) * controlDir, 0.001f));
        LookTarget(col->GetWorldPos() + controlDir);
        if (dodgeRoll->isAniStop())
        {
            speed = 300.0f;
            if (isCarryWP) {
                gunVector[selectWPNum]->VisibleOn();
                state = CRState::IDLEWP;
                walkWithWeapon->ChangeAnim(ANIMSTATE::STOP, 0.1f);

            }
            else {
                state = CRState::IDLE;
                walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            }
        }
    }
    gunVector[selectWPNum]->Update();
    Character::Update();
    idleWithWeapon->Update();
    walkWithWeapon->Update();
    dodgeRoll->Update();
}

void Player::Render()
{
    gunVector[selectWPNum]->Render();
    col->Render();
    switch (state)
    {
    case CRState::IDLE:
        idle->Render();
        break;
    case CRState::IDLEWP:
        idleWithWeapon->Render();
        break;
    case CRState::WALK:
        walk->Render();
        break;
    case CRState::WALKWP:
        walkWithWeapon->Render();
        break;
    case CRState::ROLL:
        dodgeRoll->Render();
        break;
    case CRState::DEATH:
        death->Render();
        break;
    }
}

void Player::LookTarget(Vector2 target)
{

    int index =
        round((Utility::DirToRadian(target - col->GetWorldPos()) + PI) / (45.0f * ToRadian));
    if (index == 8) index = 0;
    idle->frame.y = dirFrame[index];
    idleWithWeapon->frame.y = dirFrame[index];
    walk->frame.y = dirFrame[index];
    walkWithWeapon->frame.y = dirFrame[index];
    dodgeRoll->frame.y = dirFrame[index];
    death->frame.y = dirFrame[index];

    if (index == 0 or index == 1 or index == 7) {
        gunVector[selectWPNum]->GetCol()->rotation.z = -atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
        gunVector[selectWPNum]->GetCol()->SetLocalPosX(-col->scale.x * 0.3f);
        gunVector[selectWPNum]->GetCol()->SetLocalPosY(col->scale.y * 0.25f);
        //gunVector[selectWPNum]->rotation.y = PI;
        gunVector[selectWPNum]->GetCol()->rotation.x = PI;
        idle->rotation.y = PI;
        idleWithWeapon->rotation.y = PI;
        walk->rotation.y = PI;
        walkWithWeapon->rotation.y = PI;
        dodgeRoll->rotation.y = PI;
        death->rotation.y = PI;
    }
    else {
        gunVector[selectWPNum]->GetCol()->rotation.z = atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
        gunVector[selectWPNum]->GetCol()->SetLocalPosX(col->scale.x * 0.3f);
        gunVector[selectWPNum]->GetCol()->SetLocalPosY(col->scale.y * 0.25f);
        gunVector[selectWPNum]->GetCol()->rotation.y = 0.0f;
        gunVector[selectWPNum]->GetCol()->rotation.x = 0.0f;
        idle->rotation.y = 0.0f;
        idleWithWeapon->rotation.y = 0.0f;
        walk->rotation.y = 0.0f;
        walkWithWeapon->rotation.y = 0.0f;
        dodgeRoll->rotation.y = 0.0f;
        death->rotation.y = 0.0f;
    }
}
void Player::GetFromChest(GunType _type)
{
    gunVector.push_back(new ASRGun(L"Convict_Gun2.png", col, _type));
}


void Player::GoBack()
{
    if (INPUT->KeyDown(VK_RBUTTON)) {
        col->SetWorldPos(Vector2::Lerp(col->GetWorldPos()
            , beforeDashPoint + Vector2(300.0f, 300.0f) * controlDir, 0.001f));
    }
    Character::GoBack();
}
