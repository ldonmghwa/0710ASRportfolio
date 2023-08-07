#include "common.h"
#include "MainGameScene.h"


MainGameScene::MainGameScene()
{
	LIGHT->radius = 10000.0f;
	map = new ObTileMap();
	map->file = "asrMap.txt";
	map->Load();

	map->scale.x = 50.0f;
	map->scale.y = 50.0f;
	map->CreateTileCost();

	gui = new GameGUI();
	plConvict = new Player("Convict");
	boss = new Boss("Agonizer");
	Int2 tileIdx;
	int chestIdx = 0;
	int minionCount = 0;
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			tileIdx.x = j;
			tileIdx.y = i;
			if (map->GetTileState(tileIdx) == TILE_TRAP) {
				chestVector.push_back(new ASRChest());
				chestVector[chestIdx]->SetWorldPos(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - 1250.0f * 2,
						map->TilePosToWorldMiddlePos(tileIdx).y - 1250.0f * 2
					)
				);
				chestIdx++;
			}
			if (map->GetTileState(tileIdx) == TILE_PSPAWN) {
				plConvict->SetSpawnPos(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - 1250.0f * 2,
						map->TilePosToWorldMiddlePos(tileIdx).y - 1250.0f * 2
					)
				);
				plConvict->GetCol()->Update();
			}
			if (map->GetTileState(tileIdx) == TILE_MBSPAWN) {
				boss->SetSpawnPos(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - 1250.0f * 2,
						map->TilePosToWorldMiddlePos(tileIdx).y - 1250.0f * 2
					)
				);
				boss->spawnPos = Vector2(
					map->TilePosToWorldMiddlePos(tileIdx).x - 1250.0f * 2,
					map->TilePosToWorldMiddlePos(tileIdx).y - 1250.0f * 2
				);
				boss->isSetSpawning = true;
				boss->GetCol()->Update();
			}
			//if (map->GetTileState(tileIdx) == TILE_MSPAWN) {
			//	minionVector.push_back(new Monster("Minion" + to_string(minionCount), false));
			//	minionVector[minionVector.size() - 1]->SetSpawnPos(
			//		Vector2(
			//			map->TilePosToWorldMiddlePos(tileIdx).x - 1250.0f * 2,
			//			map->TilePosToWorldMiddlePos(tileIdx).y - 1250.0f * 2
			//		)
			//	);
			//	minionCount++;
			//	//minionVector[minionVector.size() - 1]->Update();
			//}
		}
	}
}

MainGameScene::~MainGameScene()
{
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) delete (*it);
	for (auto it = minionVector.begin(); it != minionVector.end(); it++) delete (*it);
	delete map;
	delete gui;
	delete plConvict;
	delete boss;
	TEXTURE->DeleteTexture(L"Chest_Open.png");
}

void MainGameScene::Init()
{
	
	for (auto it = minionVector.begin(); it != minionVector.end(); it++) {
		(*it)->SetTarget(plConvict);
		(*it)->SetTileMap(map);
		plConvict->SetTarget((*it));
	}
	boss->SetTarget(plConvict);
	plConvict->SetTarget(boss);
	boss->SetTileMap(map);
	plConvict->Init();
	for (auto it = minionVector.begin(); it != minionVector.end(); it++) {
		(*it)->Init();
	}
	boss->Init();
	gui->Init(plConvict->GetCurrentBulletNum());
	map->SetWorldPos(Vector2(-1250.0f * 2, -1250.0f * 2));
	plConvict->SetGui(gui);
}

void MainGameScene::Release()
{
}

void MainGameScene::Update()
{
	//if (INPUT->KeyPress(VK_UP)) CAM->position += UP * 300.0f * DELTA;
	//if (INPUT->KeyPress(VK_DOWN)) CAM->position += DOWN * 300.0f * DELTA;
	//if (INPUT->KeyPress(VK_LEFT)) CAM->position += LEFT * 300.0f * DELTA;
	//if (INPUT->KeyPress(VK_RIGHT)) CAM->position += RIGHT * 300.0f * DELTA;
	Int2 plIdx;
	if (map->WorldPosToTileIdx(plConvict->GetFoot(), plIdx)) {
		if (map->GetTileState(plIdx) == TILE_WALL) {
			plConvict->GoBack();
		}
	}
	

	map->Update();
	gui->Update();
	for (auto it = minionVector.begin(); it != minionVector.end(); it++) {
		(*it)->Update();
	}
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) (*it)->Update();
	plConvict->Update();
	boss->Update();
}

void MainGameScene::LateUpdate()
{
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) {
		if ((*it)->Intersect(plConvict->GetCol())) {
			if (INPUT->KeyDown('E')) {
				(*it)->OpenTheChest();
				//plConvict->GetFromChest((*it)->GetItemType());
				break;
			}
		}
	}
}

void MainGameScene::Render()
{
	map->Render();
	gui->Render();
	for (auto it = minionVector.begin(); it != minionVector.end(); it++)(*it)->Render();
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) (*it)->Render();
	plConvict->Render();
	boss->Render();

}

void MainGameScene::ResizeScreen()
{
}
