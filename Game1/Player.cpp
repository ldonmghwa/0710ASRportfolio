#include "common.h"

Player::Player(string _name)
    : Character(_name)
{
    col2 = new ObRect();
    resizeValue = 3.0f;
    playerType = PLType::PLCONVICT;
    charImg[(int)CRState::IDLE] = new ObImage(L"Char_Convict_idle.png");
    charImg[(int)CRState::IDLE]->maxFrame.x = 4;
    charImg[(int)CRState::IDLE]->maxFrame.y = 4;
    charImg[(int)CRState::IDLE]->scale.x = charImg[(int)CRState::IDLE]->imageSize.x / 4.0f * resizeValue;
    charImg[(int)CRState::IDLE]->scale.y = charImg[(int)CRState::IDLE]->imageSize.y / 4.0f * resizeValue;
    charImg[(int)CRState::IDLE]->pivot = OFFSET_B;
    charImg[(int)CRState::IDLE]->SetParentRT(*col);

    charImg[(int)CRState::IDLEWP] = new ObImage(L"Char_Convict_IdleWithWeapon.png");
    charImg[(int)CRState::IDLEWP]->maxFrame.x = 4;
    charImg[(int)CRState::IDLEWP]->maxFrame.y = 4;
    charImg[(int)CRState::IDLEWP]->scale.x =  charImg[(int)CRState::IDLEWP]->imageSize.x / 4.0f * resizeValue;
    charImg[(int)CRState::IDLEWP]->scale.y =  charImg[(int)CRState::IDLEWP]->imageSize.y / 4.0f * resizeValue;
    charImg[(int)CRState::IDLEWP]->pivot = OFFSET_B;
    charImg[(int)CRState::IDLEWP]->SetParentRT(*col);

    charImg[(int)CRState::WALK] = new ObImage(L"Char_Convict_Walking.png");
    charImg[(int)CRState::WALK]->maxFrame.x = 6;
    charImg[(int)CRState::WALK]->maxFrame.y = 4;
    charImg[(int)CRState::WALK]->scale.x = charImg[(int)CRState::WALK]->imageSize.x / 6.0f * resizeValue;
    charImg[(int)CRState::WALK]->scale.y = charImg[(int)CRState::WALK]->imageSize.y / 4.0f * resizeValue;
    charImg[(int)CRState::WALK]->pivot = OFFSET_B;
    charImg[(int)CRState::WALK]->SetParentRT(*col);

    charImg[(int)CRState::WALKWP] = new ObImage(L"Char_Convict_WalkingWithWeapon.png");
    charImg[(int)CRState::WALKWP]->maxFrame.x = 6;
    charImg[(int)CRState::WALKWP]->maxFrame.y = 4;
    charImg[(int)CRState::WALKWP]->scale.x = charImg[(int)CRState::WALKWP]->imageSize.x / 6.0f * resizeValue;
    charImg[(int)CRState::WALKWP]->scale.y = charImg[(int)CRState::WALKWP]->imageSize.y / 4.0f * resizeValue;
    charImg[(int)CRState::WALKWP]->pivot = OFFSET_B;
    charImg[(int)CRState::WALKWP]->SetParentRT(*col);

    charImg[(int)CRState::ROLL] = new ObImage(L"Char_Convict_DodgeRoll.png");
    charImg[(int)CRState::ROLL]->maxFrame.x = 9;
    charImg[(int)CRState::ROLL]->maxFrame.y = 4;
    charImg[(int)CRState::ROLL]->scale.x = charImg[(int)CRState::ROLL]->imageSize.x / 9.0f * resizeValue;
    charImg[(int)CRState::ROLL]->scale.y = charImg[(int)CRState::ROLL]->imageSize.y / 4.0f * resizeValue;
    charImg[(int)CRState::ROLL]->pivot = OFFSET_B;
    charImg[(int)CRState::ROLL]->SetParentRT(*col);

    charImg[(int)CRState::DEATH] = new ObImage(L"Char_Convict_Death1.png");
    charImg[(int)CRState::DEATH]->maxFrame.x = 11;
    charImg[(int)CRState::DEATH]->scale.x = charImg[(int)CRState::DEATH]->imageSize.x / 11.0f * resizeValue;
    charImg[(int)CRState::DEATH]->scale.y = charImg[(int)CRState::DEATH]->imageSize.y * resizeValue;
    charImg[(int)CRState::DEATH]->pivot = OFFSET_B;
    charImg[(int)CRState::DEATH]->SetParentRT(*col);

    col->scale.x = charImg[(int)CRState::IDLE]->scale.x;
    col->scale.y = charImg[(int)CRState::IDLE]->scale.y;

     col->pivot = OFFSET_B;
    col->isFilled = false;
    col2->scale.x = 1.0f;
    col2->scale.y = 1.0f;

    dirFrame[0] = 1;
    dirFrame[1] = 1;
    dirFrame[2] = 0;
    dirFrame[3] = 1;
    dirFrame[4] = 1;
    dirFrame[5] = 3;
    dirFrame[6] = 2;
    dirFrame[7] = 3;
}

Player::Player(string _name, PLType _type)
    : Character(_name)
{
    resizeValue = 3.0f;
    if (_type == PLType::PLCONVICT)
    {
        playerType = _type;
        charImg[(int)CRState::IDLE] = new ObImage(L"Char_Convict_Idle.png");
        charImg[(int)CRState::IDLE]->maxFrame.x = 4;
        charImg[(int)CRState::IDLE]->maxFrame.y = 4;
        charImg[(int)CRState::IDLE]->scale.x = charImg[(int)CRState::IDLE]->imageSize.x / 4.0f * resizeValue;
        charImg[(int)CRState::IDLE]->scale.y = charImg[(int)CRState::IDLE]->imageSize.y / 4.0f * resizeValue;
        charImg[(int)CRState::IDLE]->pivot = OFFSET_B;
        charImg[(int)CRState::IDLE]->SetParentRT(*col);

        charImg[(int)CRState::IDLEWP] = new ObImage(L"Char_Convict_IdleWithWeapon.png");
        charImg[(int)CRState::IDLEWP]->maxFrame.x = 4;
        charImg[(int)CRState::IDLEWP]->maxFrame.y = 4;
        charImg[(int)CRState::IDLEWP]->scale.x = charImg[(int)CRState::IDLEWP]->imageSize.x / 4.0f * resizeValue;
        charImg[(int)CRState::IDLEWP]->scale.y = charImg[(int)CRState::IDLEWP]->imageSize.y / 4.0f * resizeValue;
        charImg[(int)CRState::IDLEWP]->pivot = OFFSET_B;
        charImg[(int)CRState::IDLEWP]->SetParentRT(*col);

        charImg[(int)CRState::WALK] = new ObImage(L"Char_Convict_Walking.png");
        charImg[(int)CRState::WALK]->maxFrame.x = 6;
        charImg[(int)CRState::WALK]->maxFrame.y = 4;
        charImg[(int)CRState::WALK]->scale.x = charImg[(int)CRState::WALK]->imageSize.x / 6.0f * resizeValue;
        charImg[(int)CRState::WALK]->scale.y = charImg[(int)CRState::WALK]->imageSize.y / 4.0f * resizeValue;
        charImg[(int)CRState::WALK]->pivot = OFFSET_B;
        charImg[(int)CRState::WALK]->SetParentRT(*col);

        charImg[(int)CRState::WALKWP] = new ObImage(L"Char_Convict_WalkingWithWeapon.png");
        charImg[(int)CRState::WALKWP]->maxFrame.x = 6;
        charImg[(int)CRState::WALKWP]->maxFrame.y = 4;
        charImg[(int)CRState::WALKWP]->scale.x = charImg[(int)CRState::WALKWP]->imageSize.x / 6.0f * resizeValue;
        charImg[(int)CRState::WALKWP]->scale.y = charImg[(int)CRState::WALKWP]->imageSize.y / 4.0f * resizeValue;
        charImg[(int)CRState::WALKWP]->pivot = OFFSET_B;
        charImg[(int)CRState::WALKWP]->SetParentRT(*col);

        charImg[(int)CRState::ROLL] = new ObImage(L"Char_Convict_DodgeRoll.png");
        charImg[(int)CRState::ROLL]->maxFrame.x = 9;
        charImg[(int)CRState::ROLL]->maxFrame.y = 4;
        charImg[(int)CRState::ROLL]->scale.x = charImg[(int)CRState::ROLL]->imageSize.x / 9.0f * resizeValue;
        charImg[(int)CRState::ROLL]->scale.y = charImg[(int)CRState::ROLL]->imageSize.y / 4.0f * resizeValue;
        charImg[(int)CRState::ROLL]->pivot = OFFSET_B;
        charImg[(int)CRState::ROLL]->SetParentRT(*col);

        charImg[(int)CRState::DEATH] = new ObImage(L"Char_Convict_Death1.png");
        charImg[(int)CRState::DEATH]->maxFrame.x = 11;
        charImg[(int)CRState::DEATH]->scale.x = charImg[(int)CRState::DEATH]->imageSize.x / 11.0f * resizeValue;
        charImg[(int)CRState::DEATH]->scale.y = charImg[(int)CRState::DEATH]->imageSize.y * resizeValue;
        charImg[(int)CRState::DEATH]->pivot = OFFSET_B;
        charImg[(int)CRState::DEATH]->SetParentRT(*col);

        col->scale.x = charImg[(int)CRState::IDLE]->scale.x;
        col->scale.y = charImg[(int)CRState::IDLE]->scale.y;

        

    }
    else if (playerType == PLType::PLBULLET) {

    }

    col->pivot = OFFSET_B;
    col->isFilled = false;
    col->isVisible = false;


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

void Player::Init()
{
    
    Character::Init();
    gunVector.push_back(
        new GunBasic(
            L"Convict_Gun1.png",
            this, 
            target, 
            GunType::BASIC)
    );
    gunVector[0]->isVisible = false;
    gunVector[0]->Update();

    healPoint = 6;
    maxHealPoint = healPoint;
    blankBulletNum = 2;
    maxBlankBulletNum = blankBulletNum;
    gunNum = 1;
    money = 0;
    selectWPNum = 0; 

    isCarryWP = false;
    isAiming = false;
    isGunReloading = false;
    isInvincible = false;
    isBBTime = false;
    isGlitStart = false;
    isGlit = false;
    isHittingOn = false;
    isLightening = true;

    rollTime = 0.5f;
    backUpRollTime = rollTime;
    speed = 300.0f;
    backUpSpeed = speed;
    rollWeight = 1.0f;
    backUpRollWeight = rollWeight;
    blankBulletTime = 3.0f;
    backUpBlankBulletTime = blankBulletTime;
    glitTime = 2.0f;
    backUpGlitTime = glitTime;
    glitingTime = 0.1f;
    backUpGlitingTime = glitingTime;
    bloodingTime = 0.1f;
    backUpBloodingTime = bloodingTime;
    rollWeightScale = 0.5f;
    float rollDistanceVector = 300.0f;
    rollDistance = Vector2(rollDistanceVector, rollDistanceVector);
    rollDistance.Normalize();
}

void Player::Control()
{
    //if (!isControl) return;
    //계속 누를때
    controlDir = Vector2();
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
    controlDir.Normalize();col->MoveWorldPos(controlDir * DELTA * speed);
    
}

//void Player::Control1()
//{
//    cout << "1: " << plIdx.x << ", " << plIdx.y << endl;
//    cout << "2: " << lastPlIdx.x << ", " << lastPlIdx.y << endl;
//    if (plIdx.y - lastPlIdx.y > 0) {
//        isControl = false;
//        controlDir.y = 0;
//        
//        if (INPUT->KeyDown('S')) {
//            isControl = true;
//            controlDir.y = -1;
//        }
//        if (INPUT->KeyPress('A')) {
//            controlDir.x = -1;
//        }
//        else if (INPUT->KeyPress('D')) {
//            controlDir.x = 1;
//        }
//        if (plIdx.x - lastPlIdx.x > 0) {
//            controlDir.x = 1;
//        }
//        else if (plIdx.x - lastPlIdx.x < 0) {
//            controlDir.x = -1;
//        }
//        controlDir.Normalize();
//    }
//    if (plIdx.y - lastPlIdx.y > 0) {
//        isControl = false;
//        controlDir.y = 0;
//        if (INPUT->KeyDown('W')) {
//            isControl = true;
//            controlDir.y = 1;
//        }
//        if (INPUT->KeyDown('A')) {
//            isControl = true;
//            controlDir.x = -1;
//        }
//        else if (INPUT->KeyDown('D')) {
//            isControl = true;
//            controlDir.x = 1;
//        }
//        if (plIdx.x - lastPlIdx.x > 0) {
//            controlDir.x = 1;
//        }
//        else if (plIdx.x - lastPlIdx.x < 0) {
//            controlDir.x = -1;
//        }
//        controlDir.Normalize();
//    }
//    if (plIdx.x - lastPlIdx.x > 0) {
//        isControl = false;
//        controlDir.x = 0;
//        if (INPUT->KeyDown('A')) {
//            isControl = true;
//            controlDir.x = -1;
//        }
//        if (INPUT->KeyDown('W')) {
//            controlDir.y = 1;
//        }
//        else if (INPUT->KeyDown('S')) {
//            controlDir.y = -1;
//        }
//        if (plIdx.y - lastPlIdx.y > 0) {
//            controlDir.y = 1;
//        }
//        else if (plIdx.y - lastPlIdx.y < 0) {
//            controlDir.y = -1;
//        }
//        controlDir.Normalize();
//    }
//    if (plIdx.x - lastPlIdx.x < 0) {
//        isControl = false;
//        controlDir.x = 0;
//        if (INPUT->KeyDown('D')) {
//            controlDir.x = 1;
//        }
//        if (INPUT->KeyDown('W')) {
//            controlDir.y = 1;
//        }
//        else if (INPUT->KeyDown('S')){
//            controlDir.y = -1;
//        }
//        if (plIdx.y - lastPlIdx.y > 0) {
//            controlDir.y = 1;
//        }
//        else if (plIdx.y - lastPlIdx.y < 0) {
//            controlDir.y = -1;
//        }
//        controlDir.Normalize();
//    }
//    ImGui::Text("%d, %d", controlDir.x, controlDir.y);
//    if (state == CRState::WALK or state == CRState::WALKWP or state == CRState::ROLL) {
//        col->MoveWorldPos(controlDir * speed * DELTA);
//    }
//}

void Player::Update()
{
    //tileMap->WorldPosToTileIdx(GetFoot() , lastPlIdx);
    lastPos = col->GetWorldPos();
    CAM->position = col->GetWorldPos();
    for (auto it = gunVector.begin(); it != gunVector.end(); it++) (*it)->Update();
    Character::Update();
    plgui->IncreaseMoneyBar(money);
    plgui->IncreaseBoxKeyBar(chestKeyNum);
    if (tileMap->WorldPosToTileIdx(GetFoot(), plIdx)) {
        if (tileMap->GetTileState(plIdx) == TILE_WALL) {
            GoBack();
        }
    }
    if (isHittingOn) {
        bloodingTime -= DELTA;
        LIGHT->radius = 900.0f;
        LIGHT->outColor = Color(1.0f, 0.0f, 0.0f, 0.1f);
        LIGHT->select = true;
        if (bloodingTime < 0) {
            bloodingTime = backUpBloodingTime;
            isHittingOn = false;
            LIGHT->select = false;
            LIGHT->outColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
        }
    }
    if (isGlitStart) {
        isInvincible = true;
        Character::Glit();
    }
    if (gunVector[selectWPNum]->GetIsCylinderEmpty() 
        and gunVector[selectWPNum]->isReloading) {
        gunVector[selectWPNum]->GunReLoading(isGunReloading);
    }
    if (INPUT->KeyDown('B')) {
        col->SetWorldPos(bossRoomPos);
    }
    if (INPUT->KeyDown(VK_F1)) {
        if (isInvincible) isInvincible = false;
        else  isInvincible = true;
        if (isInvincible) speed = 1500.0f;
        else speed = backUpSpeed;
    }
    if (INPUT->KeyDown(VK_SPACE)) {
        if (!isGlitStart){
            if (blankBulletNum > 0) {
                blankBulletNum -= 1;
                glitTime = 10.0f;
                plgui->ReduceBBBar();
                isGlitStart = true;
                isInvincible = true;
            }
        }
    }
    if (state == CRState::IDLE)
    {
        LookTarget(INPUT->GetWorldMousePos());

        //idle ->walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = CRState::WALK;
            charImg[(int)CRState::WALK]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if (!isGunReloading) {
            if (INPUT->KeyDown('1')) {
                selectWPNum = '1' - '0' - 1;
                isCarryWP = true;
                gunVector[selectWPNum]->isVisible = true;
                reloadPerSec = (gunVector[selectWPNum]->GetReloadTime() - 0.1f) / gunVector[selectWPNum]->GetBulletNum();
                backUpReloadPerSec = reloadPerSec;
                state = CRState::IDLEWP;
                charImg[(int)CRState::IDLEWP]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
            }
            if (INPUT->KeyDown('2')) {
                if (gunVector.size() >= '2' - '0') {
                    selectWPNum = '2' - '0' - 1;
                    isCarryWP = true;
                    gunVector[selectWPNum]->isVisible = true;
                    reloadPerSec = (gunVector[selectWPNum]->GetReloadTime() - 0.1f) / gunVector[selectWPNum]->GetBulletNum();
                    backUpReloadPerSec = reloadPerSec;
                    state = CRState::IDLEWP;
                    charImg[(int)CRState::IDLEWP]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                }
            }
        }
    }
    else if (state == CRState::IDLEWP) {
        LookTarget(INPUT->GetWorldMousePos());

        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = CRState::WALKWP;
            charImg[(int)CRState::WALKWP]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if (INPUT->KeyDown(VK_LBUTTON)) {
            if (gunVector[selectWPNum]->GetGunType() == GunType::BASIC) {
                gunVector[selectWPNum]->FireBullet();
            }
            else if (gunVector[selectWPNum]->GetGunType() == GunType::GUIDE
                and isAiming) {
                isAiming = false;
            }
        }
        if (INPUT->KeyDown('Q')) {
            isAiming = true;
            if (gunVector[selectWPNum]->GetGunType() == GunType::GUIDE) {
                gunVector[selectWPNum]->FireBullet();
            }
        }
        if (INPUT->KeyDown('R')) {
            if (gunVector[selectWPNum]->GetIsCylinderEmpty()) {
                gunVector[selectWPNum]->isReloading = true;
                isGunReloading = true;
            }
        }
        if (isCarryWP and !isGunReloading) {
            if (INPUT->KeyDown('1')) {
                if (selectWPNum != '1' - '0' - 1) {
                    gunVector[selectWPNum]->isVisible = false;
                    selectWPNum = '1' - '0' - 1;
                    gunVector[selectWPNum]->isVisible = true;
                }
                else {
                    gunVector[selectWPNum]->isVisible = false;
                    isCarryWP = false;
                    state = CRState::IDLE;
                    charImg[(int)CRState::IDLE]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                }
            }
            if (INPUT->KeyDown('2')) {
                if (gunVector.size() >= '2' - '0') {
                    if (selectWPNum != '2' - '0' - 1) {
                        gunVector[selectWPNum]->isVisible = false;
                        selectWPNum = '2' - '0' - 1;
                        gunVector[selectWPNum]->isVisible = true;
                    }
                    else {
                        gunVector[selectWPNum]->isVisible = false;
                        isCarryWP = false;
                        state = CRState::IDLE;
                        charImg[(int)CRState::IDLE]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                    }
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
            charImg[(int)CRState::WALK]->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            charImg[(int)CRState::WALK]->frame.x = 0;
        }
        //walk->roll
        if (INPUT->KeyDown(VK_RBUTTON))
        {
            isInvincible = true;
            backUpDashPoint = col->GetWorldPos();
            state = CRState::ROLL;
            charImg[(int)CRState::ROLL]->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
        }
        if (INPUT->KeyDown('1')) {
            selectWPNum = '1' - '0' - 1;
            gunVector[selectWPNum]->isVisible = true;
            isCarryWP = true;
            reloadPerSec = (gunVector[selectWPNum]->GetReloadTime() - 0.1f) / gunVector[selectWPNum]->GetBulletNum();
            backUpReloadPerSec = reloadPerSec;
            state = CRState::WALKWP;
            charImg[(int)CRState::WALKWP]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if (INPUT->KeyDown('2')) {
            if (gunVector.size() >= '2' - '0') {
                selectWPNum = '2' - '0' - 1;
                isCarryWP = true;
                gunVector[selectWPNum]->isVisible = true;
                reloadPerSec = (gunVector[selectWPNum]->GetReloadTime() - 0.1f) / gunVector[selectWPNum]->GetBulletNum();
                backUpReloadPerSec = reloadPerSec;
                state = CRState::WALKWP;
                charImg[(int)CRState::WALKWP]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
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
            charImg[(int)CRState::WALKWP]->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            charImg[(int)CRState::WALKWP]->frame.x = 0;
        }
        //walk->roll
        if (INPUT->KeyDown(VK_RBUTTON))
        {
            isInvincible = true;
            backUpDashPoint = col->GetWorldPos();
            gunVector[selectWPNum]->isVisible = false;
            state = CRState::ROLL;
            charImg[(int)CRState::ROLL]->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
        }
        if (INPUT->KeyDown(VK_LBUTTON)) {
            if (gunVector[selectWPNum]->GetGunType() == GunType::BASIC) {
                gunVector[selectWPNum]->FireBullet();
            }
            else if (gunVector[selectWPNum]->GetGunType() == GunType::GUIDE
                and isAiming) {
                isAiming = false;
            }
        }
        if (INPUT->KeyDown('Q')) {
            isAiming = true;
            if (gunVector[selectWPNum]->GetGunType() == GunType::GUIDE) {
                gunVector[selectWPNum]->FireBullet();
            }
        }
        if (INPUT->KeyDown('R')) {
            if (gunVector[selectWPNum]->GetIsCylinderEmpty()) {
                isGunReloading = true;
                gunVector[selectWPNum]->isReloading = true;
            }
        }
        if (isCarryWP and !isGunReloading) {
            if (INPUT->KeyDown('1')) {
                if (selectWPNum != '1' - '0' - 1) {
                    gunVector[selectWPNum]->isVisible = false;
                    selectWPNum = '1' - '0' - 1;
                    gunVector[selectWPNum]->isVisible = true;
                }
                else {
                    gunVector[selectWPNum]->isVisible = false;
                    isCarryWP = false;
                    state = CRState::WALK;
                    charImg[(int)CRState::WALK]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                }
            }
            if (INPUT->KeyDown('2')) {
                if (gunVector.size() >= '2' - '0') {
                    if (selectWPNum != '2' - '0' - 1) {
                        gunVector[selectWPNum]->isVisible = false;
                        selectWPNum = '2' - '0' - 1;
                        gunVector[selectWPNum]->isVisible = true;
                    }
                    else {
                        gunVector[selectWPNum]->isVisible = false;
                        isCarryWP = false;
                        state = CRState::WALK;
                        charImg[(int)CRState::WALK]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
                    }
                }
            }
        }
    }
    else if (state == CRState::ROLL)
    {
        //rollTime -= DELTA;
        //rollWeight += DELTA * rollWeightScale;
        LookTarget(col->GetWorldPos() + controlDir);
        col->MoveWorldPos(500.0f * controlDir * DELTA);
        if (charImg[(int)state]->isAniStop())
        {
            //rollTime = backUpRollTime;
            isInvincible = false;
            //rollWeight = backUpRollWeight;
            speed = backUpSpeed;
            if (isCarryWP) {
                gunVector[selectWPNum]->isVisible = true;
                state = CRState::IDLEWP;
                charImg[(int)CRState::WALKWP]->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            }
            else {
                state = CRState::IDLE;
                charImg[(int)CRState::WALK]->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            }
        }
    }
    else if (state == CRState::DEATH) {
        //charImg[(int)CRState::DEATH]->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        //charImg[(int)CRState::DEATH]->Update();
        if (INPUT->KeyDown('F')) {
            healPoint = 6;
            for (int i = 0; i < healPoint; i++) {
                plgui->IncreaseHPBar();
            }
            state = CRState::IDLE;
            charImg[(int)CRState::DEATH]->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            charImg[(int)CRState::IDLE]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
    }
    
}

void Player::Render()
{
    for (auto it = gunVector.begin(); it != gunVector.end(); it++) (*it)->Render();
    Character::Render();
}

void Player::LookTarget(Vector2 target)
{
    Character::LookTarget(target);
    if(state != CRState::DEATH) charImg[(int)state]->frame.y = dirFrame[index];
    if (index == 0 or index == 1 or index == 7) {
        gunVector[selectWPNum]->GetCol()->rotation.z = -atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
        gunVector[selectWPNum]->GetCol()->SetLocalPosX(-col->scale.x * 0.3f);
        gunVector[selectWPNum]->GetCol()->SetLocalPosY(col->scale.y * 0.25f);
        //gunVector[selectWPNum]->rotation.y = PI;
        gunVector[selectWPNum]->GetCol()->rotation.x = PI;
        charImg[(int)state]->rotation.y = PI;
    }
    else {
        gunVector[selectWPNum]->GetCol()->rotation.z = atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
        gunVector[selectWPNum]->GetCol()->SetLocalPosX(col->scale.x * 0.3f);
        gunVector[selectWPNum]->GetCol()->SetLocalPosY(col->scale.y * 0.25f);
        gunVector[selectWPNum]->GetCol()->rotation.y = 0.0f;
        gunVector[selectWPNum]->GetCol()->rotation.x = 0.0f;
        charImg[(int)state]->rotation.y = 0.0f;
    }
}

void Player::GetFromChest(GunType _type)
{
    gunVector.push_back(
        new GunGuided(
            L"Convict_Gun2.png",
            this, 
            target,
            _type)
    );
    gunVector.back()->isVisible = false;
    gunVector.back()->Update();
    gunNum++;
}

void Player::AddHp()
{
    if (healPoint < maxHealPoint) {
        plgui->IncreaseHPBar();
        healPoint++;
    }
}

void Player::AddBlankBullet()
{
    if (blankBulletNum < maxBlankBulletNum) {
        plgui->IncreaseBBBar();
        blankBulletNum++;
    }
}


void Player::GoBack()
{
   Character::GoBack();
}


void Player::TakeDamage(int _damagePoint)
{
    isHittingOn = true;
    Character::TakeDamage(_damagePoint);
    plgui->ReduceHPBar();
}
