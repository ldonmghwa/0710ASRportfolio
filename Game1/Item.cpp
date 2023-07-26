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
}

void Item::Render()
{
}
