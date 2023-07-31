#include "common.h"

Character::Character()
{
	col = new ObRect();
}

Character::~Character()
{
	delete col;
	for (int i = 0; i < (int)CRState::SIZE; i++) {
		if (!charImg[i]) delete charImg[i];
	}
}	
void Character::Init()
{
	isInvincible = false;
	state = CRState::IDLE;
	charImg[(int)state]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

void Character::Control()
{
}

void Character::Update()
{
	if (healPoint <= 0) {
		isInvincible = true;
		state = CRState::DEATH;
		charImg[(int)CRState::DEATH]->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	}
	col->Update();
	charImg[(int)state]->Update();
}

void Character::Render()
{
	col->Render();
	charImg[(int)state]->Render();
}

void Character::GoBack()
{
	col->SetWorldPos(lastPos);
	Update();
}

void Character::Attack()
{
}

void Character::LookTarget(Vector2 target)
{
	index = round((Utility::DirToRadian(target - col->GetWorldPos()) + PI) / (45.0f * ToRadian));
	if (index == 8) index = 0;
}

void Character::TakeDamage()
{
	healPoint--;
}

Vector2 Character::GetFoot()
{
	//29 38
	/*Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	Utility::IntersectRectRect()*/
	//                              �߾ӿ���������ġ    ���߾���ġ ����
	return col->GetWorldPos() + dir2 * Vector2(15, 10) + Vector2(0, 10);
}
