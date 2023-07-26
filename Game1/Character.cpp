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
}

void Character::Attack()
{
}

void Character::LookTarget(Vector2 target)
{
}
