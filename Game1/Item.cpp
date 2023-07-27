#include "common.h"
Item::Item()
{
	col = new ObRect();
}
Item::~Item()
{
	delete col;
	delete img;
}
void Item::Update()
{
	col->Update();
}

void Item::Render()
{
	col->Render();
}
