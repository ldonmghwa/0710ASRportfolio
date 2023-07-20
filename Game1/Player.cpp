#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"

Player::Player()
{

    //hasAxis = true;
    {
        charImg[PLState::PLIDLE] = new ObImage(L"Char_Convict_Idle.png");
        charImg[PLState::PLIDLE]->maxFrame.x = 4;
        charImg[PLState::PLIDLE]->maxFrame.y = 4;
        charImg[PLState::PLIDLE]->scale.x = charImg[PLState::PLIDLE]->imageSize.x / 4.0f * 3.0f;
        charImg[PLState::PLIDLE]->scale.y = charImg[PLState::PLIDLE]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLIDLE]->pivot = OFFSET_B;

        charImg[PLState::PLIDLEWP] = new ObImage(L"Char_Convict_IdleWithWeapon.png");
        charImg[PLState::PLIDLEWP]->maxFrame.x = 4;
        charImg[PLState::PLIDLEWP]->maxFrame.y = 4;
        charImg[PLState::PLIDLEWP]->scale.x = charImg[PLState::PLIDLEWP]->imageSize.x / 4.0f * 3.0f;
        charImg[PLState::PLIDLEWP]->scale.y = charImg[PLState::PLIDLEWP]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLIDLEWP]->pivot = OFFSET_B;

        charImg[PLState::PLWALK] = new ObImage(L"Char_Convict_Walking.png");
        charImg[PLState::PLWALK]->maxFrame.x = 6;
        charImg[PLState::PLWALK]->maxFrame.y = 4;
        charImg[PLState::PLWALK]->scale.x = charImg[PLState::PLWALK]->imageSize.x / 6.0f * 3.0f;
        charImg[PLState::PLWALK]->scale.y = charImg[PLState::PLWALK]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLWALK]->pivot = OFFSET_B;

        charImg[PLState::PLWALKWP] = new ObImage(L"Char_Convict_WalkingWithWeapon.png");
        charImg[PLState::PLWALKWP]->maxFrame.x = 6;
        charImg[PLState::PLWALKWP]->maxFrame.y = 4;
        charImg[PLState::PLWALKWP]->scale.x = charImg[PLState::PLWALKWP]->imageSize.x / 6.0f * 3.0f;
        charImg[PLState::PLWALKWP]->scale.y = charImg[PLState::PLWALKWP]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLWALKWP]->pivot = OFFSET_B;

        charImg[PLState::PLROLL] = new ObImage(L"Char_Convict_DodgeRoll.png");
        charImg[PLState::PLROLL]->maxFrame.x = 8;
        charImg[PLState::PLROLL]->maxFrame.y = 4;
        charImg[PLState::PLROLL]->scale.x = charImg[PLState::PLROLL]->imageSize.x / 8.0f * 3.0f;
        charImg[PLState::PLROLL]->scale.y = charImg[PLState::PLROLL]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLROLL]->pivot = OFFSET_B;

        charImg[PLState::PLDEATH] = new ObImage(L"Char_Convict_Death1.png");
        charImg[PLState::PLDEATH]->maxFrame.x = 11;
        charImg[PLState::PLDEATH]->scale.x = charImg[PLState::PLDEATH]->imageSize.x / 11.0f * 3.0f;
        charImg[PLState::PLDEATH]->scale.y = charImg[PLState::PLDEATH]->imageSize.y * 3.0f;
        charImg[PLState::PLDEATH]->pivot = OFFSET_B;
    }

    this->pivot = OFFSET_B;
    this->scale.x = charImg[PLState::PLIDLE]->scale.x;
    this->scale.y = charImg[PLState::PLIDLE]->scale.y;
    this->isFilled = false;

    for (int i = 0; i < PLState::PLSIZE; i++) charImg[i]->SetParentRT(*this);

    dirFrame[0] = 1;
    dirFrame[1] = 1;
    dirFrame[2] = 0;
    dirFrame[3] = 1;
    dirFrame[4] = 1;
    dirFrame[5] = 3;
    dirFrame[6] = 2;
    dirFrame[7] = 3;
}

Player::Player(PLType type)
{//hasAxis = true;
    if (type == PLType::PLCONVICT)
    {
        charImg[PLState::PLIDLE] = new ObImage(L"Char_Convict_Idle.png");
        charImg[PLState::PLIDLE]->maxFrame.x = 4;
        charImg[PLState::PLIDLE]->maxFrame.y = 4;
        charImg[PLState::PLIDLE]->scale.x = charImg[PLState::PLIDLE]->imageSize.x / 4.0f * 3.0f;
        charImg[PLState::PLIDLE]->scale.y = charImg[PLState::PLIDLE]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLIDLE]->pivot = OFFSET_B;

        charImg[PLState::PLIDLEWP] = new ObImage(L"Char_Convict_IdleWithWeapon.png");
        charImg[PLState::PLIDLEWP]->maxFrame.x = 4;
        charImg[PLState::PLIDLEWP]->maxFrame.y = 4;
        charImg[PLState::PLIDLEWP]->scale.x = charImg[PLState::PLIDLEWP]->imageSize.x / 4.0f * 3.0f;
        charImg[PLState::PLIDLEWP]->scale.y = charImg[PLState::PLIDLEWP]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLIDLEWP]->pivot = OFFSET_B;

        charImg[PLState::PLWALK] = new ObImage(L"Char_Convict_Walking.png");
        charImg[PLState::PLWALK]->maxFrame.x = 6;
        charImg[PLState::PLWALK]->maxFrame.y = 4;
        charImg[PLState::PLWALK]->scale.x = charImg[PLState::PLWALK]->imageSize.x / 6.0f * 3.0f;
        charImg[PLState::PLWALK]->scale.y = charImg[PLState::PLWALK]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLWALK]->pivot = OFFSET_B;

        charImg[PLState::PLWALKWP] = new ObImage(L"Char_Convict_WalkingWithWeapon.png");
        charImg[PLState::PLWALKWP]->maxFrame.x = 6;
        charImg[PLState::PLWALKWP]->maxFrame.y = 4;
        charImg[PLState::PLWALKWP]->scale.x = charImg[PLState::PLWALKWP]->imageSize.x / 6.0f * 3.0f;
        charImg[PLState::PLWALKWP]->scale.y = charImg[PLState::PLWALKWP]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLWALKWP]->pivot = OFFSET_B;

        charImg[PLState::PLROLL] = new ObImage(L"Char_Convict_DodgeRoll.png");
        charImg[PLState::PLROLL]->maxFrame.x = 9;
        charImg[PLState::PLROLL]->maxFrame.y = 4;
        charImg[PLState::PLROLL]->scale.x = charImg[PLState::PLROLL]->imageSize.x / 9.0f * 3.0f;
        charImg[PLState::PLROLL]->scale.y = charImg[PLState::PLROLL]->imageSize.y / 4.0f * 3.0f;
        charImg[PLState::PLROLL]->pivot = OFFSET_B;

        charImg[PLState::PLDEATH] = new ObImage(L"Char_Convict_Death1.png");
        charImg[PLState::PLDEATH]->maxFrame.x = 11;
        charImg[PLState::PLDEATH]->scale.x = charImg[PLState::PLDEATH]->imageSize.x / 11.0f * 3.0f;
        charImg[PLState::PLDEATH]->scale.y = charImg[PLState::PLDEATH]->imageSize.y * 3.0f;
        charImg[PLState::PLDEATH]->pivot = OFFSET_B;
    }
    else if (type == PLType::PLBULLET) {

    }

    this->pivot = OFFSET_B;
    this->scale.x = charImg[PLState::PLIDLE]->scale.x;
    this->scale.y = charImg[PLState::PLIDLE]->scale.y;
    this->isFilled = false;

    for (int i = 0; i < PLState::PLSIZE; i++) charImg[i]->SetParentRT(*this);

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
    for (int i = 0; i < PLState::PLSIZE; i++) delete charImg[i];

    TEXTURE->DeleteTexture(L"Char_Convict_Idle.png");
    TEXTURE->DeleteTexture(L"Char_Convict_IdleWithWeapon.png");
    TEXTURE->DeleteTexture(L"Char_Convict_Walking.png");
    TEXTURE->DeleteTexture(L"Char_Convict_WalkingWithWeapon.png");
    TEXTURE->DeleteTexture(L"Char_Convict_DodgeRoll.png");
    TEXTURE->DeleteTexture(L"Char_Convict_Death1.png");

}

void Player::Init(Vector2 spawn)
{
    SetWorldPosX(spawn.x);
    SetWorldPosY(spawn.y);
    state = PLState::PLIDLE;
    speed = 300.0f;
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

    MoveWorldPos(controlDir * DELTA * speed);
}

void Player::Update()
{
    ImGui::Text("controlDir: %f, %f", controlDir.x, controlDir.y);
    ImGui::Text("player x, y: %f, %f", this->GetWorldPos().x, this->GetWorldPos().y);
    ImGui::Text("dash point x, y: %f, %f", (beforeDashPoint + Vector2(300.0f, 300.0f) * controlDir).x, (beforeDashPoint + Vector2(300.0f, 300.0f) * controlDir).y);
    lastPos = GetWorldPos();
    /*  if (ImGui::SliderAngle("rotX", &roll_shadow->rotation.x))
      {
          walk_shadow->rotation = roll_shadow->rotation;
      }
      if (ImGui::SliderAngle("rotY", &roll_shadow->rotation.y))
      {
          walk_shadow->rotation = roll_shadow->rotation;
      }
      if (ImGui::SliderAngle("rotZ", &roll_shadow->rotation.z))
      {
          walk_shadow->rotation = roll_shadow->rotation;
      }*/

    ObRect::Update();

    if (state == PLState::PLIDLE)
    {
        LookTarget(INPUT->GetWorldMousePos());

        //idle ->walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = PLState::PLWALK;
            charImg[PLState::PLWALK]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
    }
    else if (state == PLState::PLWALK)
    {
        LookTarget(INPUT->GetWorldMousePos());
        Control();
        //walk->idle
        if (not(INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D')))
        {
            state = PLState::PLIDLE;
            charImg[PLState::PLWALK]->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            charImg[PLState::PLWALK]->frame.x = 0;
        }
        //walk->roll
        if (INPUT->KeyDown(VK_RBUTTON))
        {
            beforeDashPoint = this->GetWorldPos();
            state = PLState::PLROLL;
            charImg[PLState::PLROLL]->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
            rollTime = 0.0f;
        }
    }
    else if (state == PLState::PLROLL)
    {
        rollTime += DELTA;

        //0 ~ 1 * 180
        //speed = (200.0f * rollTime / 0.6f * PI + 100.0f);

        //MoveWorldPos(controlDir * DELTA * speed);
        //if (rollTime < 2.0f) {
        this->SetWorldPos(Vector2::Lerp(this->GetWorldPos()
            , beforeDashPoint + Vector2(300.0f, 300.0f) * controlDir, 0.001f));
        // }
        LookTarget(GetWorldPos() + controlDir);
        //roll->idle
        if (charImg[PLState::PLROLL]->isAniStop())
        {
            speed = 200.0f;
            state = PLState::PLIDLE;
            charImg[PLState::PLWALK]->ChangeAnim(ANIMSTATE::STOP, 0.1f);
        }
    }
    charImg[PLState::PLIDLE]->Update();
    charImg[PLState::PLWALK]->Update();
    charImg[PLState::PLROLL]->Update();
}

void Player::Render()
{
    ObRect::Render();
    charImg[state]->Render();
}

void Player::LookTarget(Vector2 target)
{

    int index =
        round((Utility::DirToRadian(target - GetWorldPos()) + PI) / (45.0f * ToRadian));
    if (index == 8) index = 0;
    charImg[PLState::PLIDLE]->frame.y = dirFrame[index];
    charImg[PLState::PLWALK]->frame.y = dirFrame[index];
    charImg[PLState::PLROLL]->frame.y = dirFrame[index];
    if (index == 0 or index == 1 or index == 7) charImg[state]->rotation.y = PI;
    else charImg[state]->rotation.y = 0.0f;
}

Vector2 Player::GetFoot()
{
    //29 38
    /*Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
    Utility::IntersectRectRect()*/

    //                              중앙에서나갈위치    발중앙위치 보정
    return GetWorldPos() + dir2 * Vector2(15, 10) + Vector2(0, 10);
}

void Player::GoBack()
{
    SetWorldPos(lastPos);
    Update();
}
