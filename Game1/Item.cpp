#include "common.h"
Item::Item()
{
	isVisible = true;
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

void Item::Render(Camera* uicam)
{
	col->Render(uicam);
}
