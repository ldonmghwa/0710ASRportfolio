#include "stdafx.h"
#include "MainGameScene.h"

MainGameScene::MainGameScene()
{
	map = new ObTileMap();
	map->file = "asrMap.txt";
	map->Load();

	map->scale.x = 50.0f;
	map->scale.y = 50.0f;
	map->SetWorldPos(Vector2(-250.0f, -250.0f));

	for (int i = 0; i < HPMAX; i++) {
		hpBar[i] = new HPBar();
		hpBar[i]->heartBar[0] = new ObImage(L"HeartBarFull.png");
		hpBar[i]->heartBar[1] = new ObImage(L"HeartBarHalf.png");
		hpBar[i]->heartBar[2] = new ObImage(L"HeartBarZero.png");

		hpBar[i]->heartBar[0]->scale.x = hpBar[i]->heartBar[0]->imageSize.x * 5.0f;
		hpBar[i]->heartBar[0]->scale.y = hpBar[i]->heartBar[0]->imageSize.y * 5.0f;
		
		hpBar[i]->heartBar[1]->scale.x = hpBar[i]->heartBar[1]->imageSize.x * 5.0f;
		hpBar[i]->heartBar[1]->scale.y = hpBar[i]->heartBar[1]->imageSize.y * 5.0f;

		hpBar[i]->heartBar[2]->scale.x = hpBar[i]->heartBar[2]->imageSize.x * 5.0f;
		hpBar[i]->heartBar[2]->scale.y = hpBar[i]->heartBar[2]->imageSize.y * 5.0f;
	}
	hpBar[3]->heartBar[0]->isVisible = false;
	hpBar[4]->heartBar[0]->isVisible = false;
}

MainGameScene::~MainGameScene()
{
	delete map;
	for (int i = 0; i < HPMAX; i++) delete hpBar[i];

	TEXTURE->DeleteTexture(L"HeartBarFull.png");
	TEXTURE->DeleteTexture(L"HeartBarHalf.png");
	TEXTURE->DeleteTexture(L"HeartBarZero.png");
}

void MainGameScene::Init()
{
	curMaxHPBar = 3;
	currentIdx = curMaxHPBar - 1;
	map->SetWorldPos(Vector2(-1250.0f * 2, -1250.0f * 2));
	for (int i = 0; i < HPMAX; i++) hpBar[i]->hpBarState = HPBarState::FULL;

}

void MainGameScene::Release()
{
}

void MainGameScene::Update()
{
	if (INPUT->KeyPress('W'))
	{
		CAM->position += UP * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('S'))
	{
		CAM->position += DOWN * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('A'))
	{
		CAM->position += LEFT * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('D'))
	{
		CAM->position += RIGHT * 300.0f * DELTA;
	}
	for (int i = 0; i < curMaxHPBar; i++) {
		hpBar[i]->heartBar[0]->SetWorldPosX(CAM->position.x - 760.0f + i * 70.0f);
		hpBar[i]->heartBar[0]->SetWorldPosY(CAM->position.y + 450.0f);
		hpBar[i]->heartBar[1]->SetWorldPosX(CAM->position.x - 760.0f + i * 70.0f);
		hpBar[i]->heartBar[1]->SetWorldPosY(CAM->position.y + 450.0f);
		hpBar[i]->heartBar[2]->SetWorldPosX(CAM->position.x - 760.0f + i * 70.0f);
		hpBar[i]->heartBar[2]->SetWorldPosY(CAM->position.y + 450.0f);
		hpBar[i]->heartBar[0]->Update();
		hpBar[i]->heartBar[1]->Update();
		hpBar[i]->heartBar[2]->Update();
	}
	//Utility::Saturate(currentIdx, 0, curMaxHPBar - 1);
	if (INPUT->KeyDown('Z')) {
		if (hpBar[currentIdx]->hpBarState == HPBarState::ZERO) {
			currentIdx--;
			if (currentIdx < 0) {
				currentIdx = 0;
			}
		}
		else hpBar[currentIdx]->hpBarState += 1;
	}
	map->Update();
}

void MainGameScene::LateUpdate()
{
}

void MainGameScene::Render()
{
	map->Render(); 
	for (int i = 0; i < curMaxHPBar; i++) {
		if (hpBar[i]->hpBarState == HPBarState::FULL) hpBar[i]->heartBar[0]->Render();
		else if (hpBar[i]->hpBarState == HPBarState::HALF) hpBar[i]->heartBar[1]->Render();
		else if (hpBar[i]->hpBarState == HPBarState::ZERO) hpBar[i]->heartBar[2]->Render();
	}

}

void MainGameScene::ResizeScreen()
{
}
