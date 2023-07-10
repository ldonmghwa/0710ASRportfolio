#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"

Player::Player()
{
  
    //hasAxis = true;
    
    walk = new ObImage(L"player_walk.png");
    walk->maxFrame.x = 6;
    walk->maxFrame.y = 8;
    walk->scale.x = walk->imageSize.x / 6.0f * 3.0f;
    walk->scale.y = walk->imageSize.y / 8.0f * 3.0f;
    walk->pivot = OFFSET_B;

    walk_shadow = new ObImage(L"player_walk.png");
    walk_shadow->maxFrame.x = 6;
    walk_shadow->maxFrame.y = 8;
    walk_shadow->scale.x = walk->imageSize.x / 6.0f * 3.0f;
    walk_shadow->scale.y = walk->imageSize.y / 8.0f * 3.0f;
    walk_shadow->pivot = OFFSET_B;
    walk_shadow->color = Color(0, 0, 0,0.5);


    roll = new ObImage(L"player_roll.png");
    roll->maxFrame.x = 6;
    roll->maxFrame.y = 8;
    roll->scale.x = roll->imageSize.x / 6.0f * 3.0f;
    roll->scale.y = roll->imageSize.y / 8.0f * 3.0f;
    roll->pivot = OFFSET_B;

    roll_shadow = new ObImage(L"player_roll.png");
    roll_shadow->maxFrame.x = 6;
    roll_shadow->maxFrame.y = 8;
    roll_shadow->scale.x = roll->imageSize.x / 6.0f * 3.0f;
    roll_shadow->scale.y = roll->imageSize.y / 8.0f * 3.0f;
    roll_shadow->pivot = OFFSET_B;
    roll_shadow->color = Color(0, 0, 0, 0.5);

    this->pivot = OFFSET_B;

    scale.x = walk->scale.x * 0.6f;
    scale.y = walk->scale.y * 0.8f;

    walk->SetParentRT(*this);
    roll->SetParentRT(*this);
    walk_shadow->SetParentRT(*this);
    roll_shadow->SetParentRT(*this);
    isFilled = false;


    Frame[0] = 2;
    Frame[1] = 5;
    Frame[2] = 3;
    Frame[3] = 4;
    Frame[4] = 0;
    Frame[5] = 7;
    Frame[6] = 1;
    Frame[7] = 6;
}

Player::~Player()
{
}

void Player::Init(Vector2 spawn)
{
    SetWorldPosX(spawn.x);
    SetWorldPosY(spawn.y);
    state = PlayerState::IDLE;
    speed = 200.0f;
    roll_shadow->isVisible = roll->isVisible = false;
    roll_shadow->rotation.x = PI;
    walk_shadow->rotation.x = PI;
}

void Player::Control()
{
    dir = Vector2();

    //��� ������
    if (INPUT->KeyPress('W'))
    {
        dir.y = 1.0f;
    }
    else if (INPUT->KeyPress('S'))
    {
        dir.y = -1.0f;
    }
    if (INPUT->KeyPress('A'))
    {
        dir.x = -1.0f;
    }
    else if (INPUT->KeyPress('D'))
    {
        dir.x = 1.0f;
    }
    dir2 = dir;
    dir.Normalize();

    MoveWorldPos(dir * DELTA * speed);
}

void Player::Update()
{
    walk->color = roll->color = color;
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
   
    if (state == PlayerState::IDLE)
    {
        LookTarget(INPUT->GetWorldMousePos());


        //idle ->walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = PlayerState::WALK;
            walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
    }
    else if (state == PlayerState::WALK)
    {
        LookTarget(INPUT->GetWorldMousePos());
        Control();
        //walk->idle
        if (not(INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D')))
        {
            state = PlayerState::IDLE;
            walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            walk->frame.x = 0;
        }
        //walk->roll
        if (INPUT->KeyDown(VK_SPACE))
        {
            state = PlayerState::ROLL;
            roll->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
            roll_shadow->isVisible = roll->isVisible = true;
            walk_shadow-> isVisible= walk->isVisible = false;
            rollTime = 0.0f;
        }
    }
    else if (state == PlayerState::ROLL)
    {
        rollTime += DELTA;

        //0 ~ 1 * 180
        speed = (250.0f * rollTime / 0.6f * PI + 100.0f);

        MoveWorldPos(dir * DELTA * speed);
        LookTarget(GetWorldPos() + dir);
        //roll->idle
        if (roll->isAniStop())
        {
            speed = 200.0f;
            state = PlayerState::IDLE;
            walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            roll_shadow->isVisible = roll->isVisible = false;
            walk_shadow->isVisible = walk->isVisible = true;
        }
    }
    walk->Update();
    roll->Update();
    roll_shadow->Update();
    walk_shadow->Update();
}

void Player::Render()
{
    ObRect::Render();
    roll_shadow->frame = roll->frame;
    walk_shadow->frame = walk->frame;
    roll_shadow->Render();
    walk_shadow->Render();
    walk->Render();
    roll->Render();
  
  
}

void Player::LookTarget(Vector2 target)
{

    int index =
        round((Utility::DirToRadian(target - GetWorldPos()) + PI) / (45.0f * ToRadian));
    if (index == 8)index = 0;

    walk->frame.y = Frame[index];
    roll->frame.y = Frame[index];
}

Vector2 Player::GetFoot()
{
    //29 38
    /*Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
    Utility::IntersectRectRect()*/

    //                              �߾ӿ���������ġ    ���߾���ġ ����
    return GetWorldPos() + dir2 * Vector2(15,10) + Vector2(0, 10);
}

void Player::GoBack()
{
    SetWorldPos(lastPos);
    Update();
}
