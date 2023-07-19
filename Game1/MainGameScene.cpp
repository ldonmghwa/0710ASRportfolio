#include "stdafx.h"
#include "GameGUI.h"
#include "MainGameScene.h"

MainGameScene::MainGameScene()
{
	map = new ObTileMap();
	map->file = "asrMap.txt";
	map->Load();

	map->scale.x = 50.0f;
	map->scale.y = 50.0f;
	map->SetWorldPos(Vector2(-250.0f, -250.0f));

	gui = new GameGUI();
}

MainGameScene::~MainGameScene()
{
	delete map;
	delete gui;
}

void MainGameScene::Init()
{
	gui->Init();
	map->SetWorldPos(Vector2(-1250.0f * 2, -1250.0f * 2));
}

void MainGameScene::Release()
{
}

void MainGameScene::Update()
{
	if (INPUT->KeyPress('W')) CAM->position += UP * 300.0f * DELTA;
	if (INPUT->KeyPress('S')) CAM->position += DOWN * 300.0f * DELTA;
	if (INPUT->KeyPress('A')) CAM->position += LEFT * 300.0f * DELTA;
	if (INPUT->KeyPress('D')) CAM->position += RIGHT * 300.0f * DELTA;

	map->Update();
	gui->Update();
}

void MainGameScene::LateUpdate()
{
}

void MainGameScene::Render()
{
	map->Render();
	gui->Render();
}

void MainGameScene::ResizeScreen()
{
}
