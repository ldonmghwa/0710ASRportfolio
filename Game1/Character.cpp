#include "common.h"

Character::Character()
{
	col = new ObRect();
}

Character::~Character()
{
	delete col;
	delete idle;
	delete death;
	delete walk;
}	
void Character::Init(Vector2 spawn)
{
}

void Character::Control()
{
}

void Character::Update()
{
	col->Update();
	idle->Update();
	walk->Update();
	death->Update();
}

void Character::Render()
{
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

}

Vector2 Character::GetFoot()
{
	//29 38
	/*Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	Utility::IntersectRectRect()*/
	//                              중앙에서나갈위치    발중앙위치 보정
	return col->GetWorldPos() + dir2 * Vector2(15, 10) + Vector2(0, 10);
}
