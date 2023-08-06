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
    gun->shootScene[(int)BossScene::GUIDE] = true;
    isSetSpawning = true;
    healPoint = 100;
    gun->shootSceneIdx = (int)BossScene::GUIDE;
    speed = 70.0f;
    detectionRange = 900.0f;
    attackRange = detectionRange;
    shootingInterval = 2.0f;
    backUpShootingInterval = shootingInterval;
    shootSceneChangeTime = 6.5f;
    backUpShootSceneChangeTime = shootSceneChangeTime;

    mazeBulletLifeTime = 12.5f;
    backUpMazeBulletLifeTime = mazeBulletLifeTime;
    source = col->GetWorldPos();
    dest = col->GetWorldPos();
}

void Boss::Update()
{
    lastPos = col->GetWorldPos();
    gun->Update();
    Character::Update();

    if (gun->GetIsCylinderEmpty()) {
        gun->GunReLoading();
    }
    if (state == CRState::IDLE)
    {
        LookTarget(target[0]->GetCol()->GetWorldPos());
        if ((col->GetWorldPos() - target[0]->GetCol()->GetWorldPos()).Length() < detectionRange) {
            shootingInterval = backUpShootingInterval;
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
        ImGui::Text("%d", gun->shootSceneIdx);
        LookTarget(target[0]->GetCol()->GetWorldPos());
        Int2 monsterIdx;
        if (shootSceneChangeTime < 0) {
            gun->shootScene[gun->shootSceneIdx] = false;
            gun->shootSceneIdx += 1;
            if (gun->shootSceneIdx == (int)BossScene::SIZE)
                gun->shootSceneIdx = (int)BossScene::BASIC;
            gun->shootScene[gun->shootSceneIdx] = true;
            shootingInterval = backUpShootingInterval;
            shootSceneChangeTime = backUpShootSceneChangeTime;
        }
        if (gun->shootScene[(int)BossScene::BASIC]) {
            shootSceneChangeTime -= DELTA;
            shootingInterval -= DELTA;
            if (shootingInterval < 0) {
                shootingInterval = backUpShootingInterval;
                gun->FireBullet();
            }
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
        else if (gun->shootScene[(int)BossScene::MAZE]) {
            shootSceneChangeTime = backUpShootSceneChangeTime;
            mazeBulletLifeTime -= DELTA;
            this->col->SetWorldPos(spawnPos);
            if (isSetSpawning) {
                target[0]->GetCol()->SetWorldPosX(spawnPos.x);
                target[0]->GetCol()->SetWorldPosY(spawnPos.y - 700.0f);
                gun->MazeBullet();
                isSetSpawning = false;
            }
            if (mazeBulletLifeTime < 0) {
                gun->shootScene[gun->shootSceneIdx] = false;
                gun->shootSceneIdx += 1;
                gun->shootScene[gun->shootSceneIdx] = true;
                shootingInterval = backUpShootingInterval;
                mazeBulletLifeTime = backUpMazeBulletLifeTime;
            }
        }
        else if (gun->shootScene[(int)BossScene::GUIDE]) {
            shootSceneChangeTime -= DELTA;
            shootingInterval -= DELTA;
            if (shootingInterval < 0) {
                shootingInterval = backUpShootingInterval;
                gun->GuideBullet(target[0]);
            }
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
    }
    else if (state == CRState::DEATH) {
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

void Boss::LookTarget(Vector2 target)
{
    Character::LookTarget(target);
    gun->GetCol()->rotation.z = atan2f((target - col->GetWorldPos()).y, (target - col->GetWorldPos()).x);
}
