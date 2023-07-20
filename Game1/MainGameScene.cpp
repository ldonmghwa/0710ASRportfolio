#include "stdafx.h"
#include "GameGUI.h"
#include "Player.h"
#include "MainGameScene.h"

MainGameScene::MainGameScene()
{
	map = new ObTileMap();
	map->file = "asrMap.txt";
	map->Load();

	map->scale.x = 50.0f;
	map->scale.y = 50.0f;

	gui = new GameGUI();
	plConvict = new Player(PLType::PLCONVICT);
}

MainGameScene::~MainGameScene()
{
	delete map;
	delete gui;
	delete plConvict;
}

void MainGameScene::Init()
{
	gui->Init();
	plConvict->Init(Vector2(0, 0));
	map->SetWorldPos(Vector2(-1250.0f * 2, -1250.0f * 2));
}

void MainGameScene::Release()
{
}

void MainGameScene::Update()
{
	if (INPUT->KeyPress(VK_UP)) CAM->position += UP * 300.0f * DELTA;
	if (INPUT->KeyPress(VK_DOWN)) CAM->position += DOWN * 300.0f * DELTA;
	if (INPUT->KeyPress(VK_LEFT)) CAM->position += LEFT * 300.0f * DELTA;
	if (INPUT->KeyPress(VK_RIGHT)) CAM->position += RIGHT * 300.0f * DELTA;

	map->Update();
	gui->Update();
	plConvict->Update();
}

void MainGameScene::LateUpdate()
{
}

void MainGameScene::Render()
{
	map->Render();
	gui->Render();
	plConvict->Render();

}

void MainGameScene::ResizeScreen()
{
}
