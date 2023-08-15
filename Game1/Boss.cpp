#include "common.h"

Boss::Boss(string _name) : Character(_name)
{

	monsterType = MTType::BOSS;
	resizeValue = 3.0f;
    charImg[(int)CRState::IDLE] = new ObImage(L"Agonizer_Idle.png");
    charImg[(int)CRState::IDLE]->maxFrame.x = 1;
    charImg[(int)CRState::IDLE]->scale.x = charImg[(int)CRState::IDLE]->imageSize.x * resizeValue;
    charImg[(int)CRState::IDLE]->scale.y = charImg[(int)CRState::IDLE]->imageSize.y * resizeValue;
    charImg[(int)CRState::IDLE]->pivot = OFFSET_B;
    charImg[(int)CRState::IDLE]->SetParentRT(*col);

    charImg[(int)CRState::WALK] = new ObImage(L"Agonizer_Idle.png");
    charImg[(int)CRState::WALK]->maxFrame.x = 1;
    charImg[(int)CRState::WALK]->scale.x = charImg[(int)CRState::WALK]->imageSize.x * resizeValue;
    charImg[(int)CRState::WALK]->scale.y = charImg[(int)CRState::WALK]->imageSize.y * resizeValue;
    charImg[(int)CRState::WALK]->pivot = OFFSET_B;
    charImg[(int)CRState::WALK]->SetParentRT(*col);

    charImg[(int)CRState::HIT] = new ObImage(L"Agonizer_Attack.png");
    charImg[(int)CRState::HIT]->maxFrame.x = 8;
    charImg[(int)CRState::HIT]->scale.x = charImg[(int)CRState::HIT]->imageSize.x / 8.0f * resizeValue;
    charImg[(int)CRState::HIT]->scale.y = charImg[(int)CRState::HIT]->imageSize.y * resizeValue;
    charImg[(int)CRState::HIT]->pivot = OFFSET_B;
    charImg[(int)CRState::HIT]->SetParentRT(*col);

    charImg[(int)CRState::DEATH] = new ObImage(L"Agonizer_Death.png");
    charImg[(int)CRState::DEATH]->maxFrame.x = 3;
    charImg[(int)CRState::DEATH]->scale.x = charImg[(int)CRState::DEATH]->imageSize.x / 3.0f * resizeValue;
    charImg[(int)CRState::DEATH]->scale.y = charImg[(int)CRState::DEATH]->imageSize.y * resizeValue;
    charImg[(int)CRState::DEATH]->pivot = OFFSET_B;
    charImg[(int)CRState::DEATH]->SetParentRT(*col);
    charImg[(int)CRState::DEATH]->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

    col->scale.x = charImg[(int)CRState::IDLE]->scale.x;
    col->scale.y = charImg[(int)CRState::IDLE]->scale.y;
    col->pivot = OFFSET_B;
    col->isVisible = false;
    col->isFilled = false;

    dirFrame[0] = 0;
    dirFrame[1] = 0;
    dirFrame[2] = 0;
    dirFrame[3] = 0;
    dirFrame[4] = 0;
    dirFrame[5] = 0;
    dirFrame[6] = 0;
    dirFrame[7] = 0;
}

Boss::~Boss()
{
    TEXTURE->DeleteTexture(L"Agonizer_Idle.png");
    TEXTURE->DeleteTexture(L"Agonizer_Attack.png");
    TEXTURE->DeleteTexture(L"Agonizer_Death.png");
    TEXTURE->DeleteTexture(L"Agonizer_Gun.png");
    TEXTURE->DeleteTexture(L"Agonizer_Bullet_Basic.png");
    TEXTURE->DeleteTexture(L"Agonizer_Bullet_Guided.png");
}

void Boss::Init()
{
    gun = new GunBoss(L"Agonizer_Gun.png",
        this,
        target,
        GunType::BOSS);
    Character::Init();
    gun->shootScene[(int)BossScene::BASIC] = true;
    gun->shootSceneIdx = (int)BossScene::BASIC;
    isRotateChange = true;
    isSetSpawning = true;
    healPoint = 50;
    speed = 70.0f;
    backUpSpeed = speed;

    detectionRange = 700.0f;
    attackRange = detectionRange;

    basicShootingInterval = 2.0f;
    backUpBasicShootingInterval = basicShootingInterval;
    guidedShootingInterval = 1.5f;
    backUpGuidedShootingInterval = guidedShootingInterval;
    rotateShootingInterval = 0.1f;
    backUpRotateShootingInterval = rotateShootingInterval;
    shootSceneChangeTime = 10.5f;
    backUpShootSceneChangeTime = shootSceneChangeTime;
    gun->guidedShootingInterval = guidedShootingInterval;
    rotateGuideShootingInterval = 0.2f;
    backUpRotateGuideShootingInterval = rotateGuideShootingInterval;

    glitTime = 0.4f;
    backUpGlitTime = glitTime;
    glitingTime = 0.1f;
    backUpGlitingTime = glitingTime;

    incrementValue = 0.0f;
    mazeBulletLifeTime = 10.5f;
    backUpMazeBulletLifeTime = mazeBulletLifeTime;
    source = col->GetWorldPos();
    dest = col->GetWorldPos();
}

void Boss::Update()
{
    lastPos = col->GetWorldPos();
    gun->Update();
    Character::Update();
    Character::Glit();
    if (gun->GetIsCylinderEmpty()) {
        gun->GunReLoading();
    }
    if (state == CRState::IDLE)
    {
        mazeBulletLifeTime = gun->GetMazeBulletLifeTime();
        LookTarget(target[0]->GetCol()->GetWorldPos());
        if ((col->GetWorldPos() - target[0]->GetCol()->GetWorldPos()).Length() < detectionRange) {
            basicShootingInterval = backUpBasicShootingInterval;
            state = CRState::WALK;
            charImg[(int)CRState::WALK]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
    }
    else if (state == CRState::WALK)
    {
        LookTarget(target[0]->GetCol()->GetWorldPos());
        if ((col->GetWorldPos() - target[0]->GetCol()->GetWorldPos()).Length() >= detectionRange) {
            state = CRState::IDLE;
            charImg[(int)CRState::IDLE]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        if ((col->GetWorldPos() - target[0]->GetCol()->GetWorldPos()).Length() < attackRange) {
            state = CRState::HIT;
            charImg[(int)CRState::HIT]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
        Int2 monsterIdx;
        if (tileMap->PathFinding(col->GetWorldPos(),
            target[0]->GetCol()->GetWorldPos(),
            targetWay)) {
            if (targetWay.size() > 0) {
                Vector2 source = targetWay.back()->Pos;
                targetWay.pop_back();
                Vector2 dest = targetWay.back()->Pos;
                Vector2 dir = dest - source;
                dir.Normalize();
                col->MoveWorldPos(dir * speed * DELTA);

            }
        }
    }
    else if (state == CRState::HIT) {
        Int2 monsterIdx;
        if (shootSceneChangeTime < 0) {
            gun->shootScene[gun->shootSceneIdx] = false;
            gun->shootSceneIdx += 1;
            if (gun->shootSceneIdx == (int)BossScene::SIZE)
                gun->shootSceneIdx = (int)BossScene::BASIC;
            if (speed != backUpSpeed) speed = backUpSpeed;
            gun->shootScene[gun->shootSceneIdx] = true;
            basicShootingInterval = backUpBasicShootingInterval;
            guidedShootingInterval = backUpGuidedShootingInterval;
            shootSceneChangeTime = backUpShootSceneChangeTime;
        }
        if (gun->shootScene[(int)BossScene::BASIC]) {
            LookTarget(target[0]->GetCol()->GetWorldPos());
            shootSceneChangeTime -= DELTA;
            basicShootingInterval -= DELTA;

            if (basicShootingInterval < 0) {
                basicShootingInterval = backUpBasicShootingInterval;
                gun->FireBullet(10.0f, 500.0f);
            }
            TargetSearch();
        }
        else if (gun->shootScene[(int)BossScene::MAZE]) {
            shootSceneChangeTime = backUpShootSceneChangeTime;
            mazeBulletLifeTime -= DELTA;
            this->col->SetWorldPos(spawnPos);
            if (isSetSpawning) {
                target[0]->GetCol()->SetWorldPosX(target[0]->bossRoomPos.x);
                target[0]->GetCol()->SetWorldPosY(target[0]->bossRoomPos.y);
                gun->MazeBullet();
                isSetSpawning = false;
            }
            if (mazeBulletLifeTime < 0) {
                gun->shootScene[gun->shootSceneIdx] = false;
                gun->shootSceneIdx += 1;
                gun->shootScene[gun->shootSceneIdx] = true;
                isSetSpawning = true;
                basicShootingInterval = backUpBasicShootingInterval;
                mazeBulletLifeTime = backUpMazeBulletLifeTime;
            }
        }
        else if (gun->shootScene[(int)BossScene::ROTATE]) {
            speed = 100.0f;
            shootSceneChangeTime -= DELTA;
            rotateShootingInterval -= DELTA;
            /*if (isRotateChange) {
                incrementValue += DELTA;
                if (incrementValue > 2.5f) isRotateChange = false;
            }
            else {
                incrementValue -= DELTA;
                if (incrementValue < -2.5f) isRotateChange = true;
            }*/
            gun->GetCol()->rotation.z -= DELTA * 5.0f;
            if (rotateShootingInterval < 0) {
                rotateShootingInterval = backUpRotateShootingInterval;
                gun->RotateBullet(5.0f, 300.0f);
                speed = backUpSpeed;
            }
            TargetSearch();
        }
        else if (gun->shootScene[(int)BossScene::GUIDE]) {
            LookTarget(target[0]->GetCol()->GetWorldPos());
            shootSceneChangeTime -= DELTA;
            guidedShootingInterval -= DELTA;
            if (guidedShootingInterval < 0) {
                guidedShootingInterval = backUpGuidedShootingInterval;
                gun->GuideBullet();
            }
            TargetSearch();
        }
        else if (gun->shootScene[(int)BossScene::ROTATEGUIDE]) {
            shootSceneChangeTime -= DELTA;
            rotateGuideShootingInterval -= DELTA;
            //gun->GetCol()->rotation.z -= DELTA * 5.0f;
            if (rotateGuideShootingInterval < 0) {
                rotateGuideShootingInterval = backUpRotateGuideShootingInterval;
                gun->RotateGuideBullet();
            }
        }
    }
    else if (state == CRState::DEATH) {
        moneyCount++;
        if (moneyCount < 2) {
            target[0]->IncreaseMoney(100);
        }

        //cout << charImg[(int)CRState::DEATH]->frame.x << endl;
        //ImGui::Text("minion death frame.x %d", charImg[(int)CRState::DEATH]->frame.x);

        //charImg[(int)CRState::DEATH]->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
        //charImg[(int)CRState::DEATH]->frame.x++;
    }
}

void Boss::Render()
{
    Character::Render();
    gun->Render();
}

void Boss::TargetSearch()
{
    if (tileMap->PathFinding(col->GetWorldPos(),
        target[0]->GetCol()->GetWorldPos(),
        targetWay)) {
        if (targetWay.size() > 0) {
            Vector2 source = targetWay.back()->Pos;
            targetWay.pop_back();
            Vector2 dest = targetWay.back()->Pos;
            Vector2 dir = dest - source;
            dir.Normalize();
            col->MoveWorldPos(dir * speed * DELTA);
        }
    }
}

void Boss::LookTarget(Vector2 target)
{
    Character::LookTarget(target);
    gun->GetCol()->rotation.z = atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
}
