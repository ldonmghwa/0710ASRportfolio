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
	correctionValue = Vector2(map->scale.x * map->GetTileSize().x, map->scale.y * map->GetTileSize().y);
	cout << "correctionValue: " << correctionValue.x << ", " << correctionValue.y << endl;
	gui = new GameGUI();
	plConvict = new Player("Convict");
	boss = new Boss("Agonizer");
	Int2 tileIdx;
	Int2 tileIdx2;
	int chestIdx = 0;
	int minionCount = 0;
	for (int i = 0; i < map->GetTileSize().y; i++) {
		for (int j = 0; j < map->GetTileSize().x; j++) {
			tileIdx.x = j;
			tileIdx.y = i;
			if (map->GetTileState(tileIdx) == TILE_TRAP) {
				chestVector.push_back(new ASRChest());
				chestVector[chestIdx]->SetWorldPos(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - correctionValue.x,
						map->TilePosToWorldMiddlePos(tileIdx).y - correctionValue.y
					)
				);
				chestIdx++;
			}
			if (map->GetTileState(tileIdx) == TILE_PSPAWN) {
				plConvict->SetSpawnPos(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - correctionValue.x,
						map->TilePosToWorldMiddlePos(tileIdx).y - correctionValue.y
					)
				);
				plConvict->GetCol()->Update();
			}
			
			/*if (map->GetTileState(tileIdx) == TILE_MSPAWN) {
				minionVector.push_back(new Monster("Minion" + to_string(minionCount), false));
				minionVector[minionVector.size() - 1]->SetSpawnPos(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - correctionValue.x,
						map->TilePosToWorldMiddlePos(tileIdx).y - correctionValue.y
					)
				);
				minionCount++;
			}*/
			if (map->GetTileState(tileIdx) == TILE_PSPAWNB) {
				plConvict->bossRoomPos =
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - correctionValue.x,
						map->TilePosToWorldMiddlePos(tileIdx).y - correctionValue.y
					);
				plConvict->GetCol()->Update();
			}
			if (map->GetTileState(tileIdx) == TILE_MBSPAWN) {
				boss->SetSpawnPos(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx).x - correctionValue.x,
						map->TilePosToWorldMiddlePos(tileIdx).y - correctionValue.y
					)
				);
				boss->spawnPos = Vector2(
					map->TilePosToWorldMiddlePos(tileIdx).x - correctionValue.x,
					map->TilePosToWorldMiddlePos(tileIdx).y - correctionValue.y
				);
				boss->isSetSpawning = true;
				boss->GetCol()->Update();
			}
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
		(*it)->tileMap = map;
		plConvict->SetTarget((*it));
	}
	boss->SetTarget(plConvict);
	plConvict->SetTarget(boss);
	boss->tileMap = map;
	plConvict->tileMap = map;
	plConvict->Init();
	for (auto it = minionVector.begin(); it != minionVector.end(); it++) {
		(*it)->Init();
	}
	boss->Init();
	gui->Init(plConvict->GetCurrentBulletNum());
	//map->SetWorldPos(Vector2(-1250.0f * 2, -1250.0f * 2));
	map->SetWorldPos(-correctionValue);
	plConvict->SetGui(gui);
	plConvict->chestKeyNum = chestVector.size();
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
	/*Int2 plIdx;
	if (map->WorldPosToTileIdx(plConvict->GetFoot(), plIdx)) {
		if (map->GetTileState(plIdx) == TILE_WALL) {
			plConvict->GoBack();
		}
	}*/
	
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
	if (plConvict->chestKeyNum > 0) {
		for (auto it = chestVector.begin(); it != chestVector.end(); it++) {
			if ((*it)->Intersect(plConvict->GetCol())) {
				if (INPUT->KeyDown('E')) {
					(*it)->OpenTheChest();
					plConvict->chestKeyNum--;
					if (plConvict->gunNum < 2) {
						plConvict->GetFromChest((*it)->GetItemType());
					}
					else if (RANDOM->Int(0, 99) < 60) {
						plConvict->IncreaseMoney(10);
					}
					else if (RANDOM->Int(0, 99) < 80) {
						plConvict->AddHp();
					}
					else if (RANDOM->Int(0, 99) < 100) {
						plConvict->AddBlankBullet();
					}
					break;
				}
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
