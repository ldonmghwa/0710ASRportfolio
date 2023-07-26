#include "common.h"

ASRChest::ASRChest()
{
	open = new ObImage(L"Chest_Open.png");
	open->scale.x = open->imageSize.x / 6.0f * 1.5f;
	open->scale.y = open->imageSize.y * 1.5f;
	open->maxFrame.x = 6;
	open->ChangeAnim(ANIMSTATE::STOP, 0.1f);

	gunType = GunType::GUIDE;
	isOpen = false;
	isExist = true;
	this->scale = open->scale * 1.5f;
	this->isFilled = false;
	open->SetParentRT(*this);
	disappearTime = 0.0f;
	glitteringTime = 0.1f;
}

ASRChest::~ASRChest()
{
	delete open;
}

void ASRChest::Update()
{
	if (not isExist) return;
	ObRect::Update();
	open->Update();
	ImGui::Text("%d", open->frame.x);
	if (open->frame.x == 5) {
		if (disappearTime > 0) {
			if (isGlit) {
				open->color.w = 0.0f;
				if (glitteringTime > 0) glitteringTime -= DELTA;
				else isGlit = false;
			}
			else {
				open->color.w = 0.5f;
				if (glitteringTime < 0.1f) glitteringTime += DELTA;
				else isGlit = true;
			}
			disappearTime -= DELTA;
			if (disappearTime <= 0) isExist = false;
		}
	}
	
}

void ASRChest::Render()
{
	if (not isExist) return;
	ObRect::Render();
	open->Render();
}

void ASRChest::OpenTheChest()
{
	open->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	disappearTime = 2.0f;
}
