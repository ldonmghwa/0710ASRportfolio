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

}

MainGameScene::~MainGameScene()
{
}

void MainGameScene::Init()
{
}

void MainGameScene::Release()
{
}

void MainGameScene::Update()
{
	if (INPUT->KeyDown('1'))
	{
		SCENE->ChangeScene("INTROSCENE", 1.0f);
		fadeout = 1.0f;
	}

	if (fadeout > 0.0f)
	{
		fadeout -= DELTA;
		LIGHT->lightColor.x = fadeout / 2.0f;
		LIGHT->lightColor.y = fadeout / 2.0f;
		LIGHT->lightColor.z = fadeout / 2.0f;
	}
	map->Update();
}

void MainGameScene::LateUpdate()
{
}

void MainGameScene::Render()
{
	map->Render();
}

void MainGameScene::ResizeScreen()
{
}
