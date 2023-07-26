#include "common.h"
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

	Int2 tileIdx;
	Int2 tileIdx2;
	cout << map->GetTileSize().x << ", " << map->GetTileSize().y << endl;
	int chestIdx = 0;
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
			tileIdx2.x = j;
			tileIdx2.y = i;
			if (map->GetTileState(tileIdx2) == TILE_SPAWN) {
				plConvict->Init(
					Vector2(
						map->TilePosToWorldMiddlePos(tileIdx2).x - 1250.0f * 2,
						map->TilePosToWorldMiddlePos(tileIdx2).y - 1250.0f * 2
					)
				);
			}

		}
	}
}

MainGameScene::~MainGameScene()
{
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) delete (*it);
	delete map;
	delete gui;
	delete plConvict;

	TEXTURE->DeleteTexture(L"Chest_Open.png");
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
	if (INPUT->KeyPress(VK_UP)) CAM->position += UP * 300.0f * DELTA;
	if (INPUT->KeyPress(VK_DOWN)) CAM->position += DOWN * 300.0f * DELTA;
	if (INPUT->KeyPress(VK_LEFT)) CAM->position += LEFT * 300.0f * DELTA;
	if (INPUT->KeyPress(VK_RIGHT)) CAM->position += RIGHT * 300.0f * DELTA;
	Int2 plIdx;
	if (map->WorldPosToTileIdx(plConvict->GetFoot(), plIdx)) {
		if (map->GetTileState(plIdx) == TILE_WALL) {
			plConvict->GoBack();
		}
	}

	map->Update();
	gui->Update();
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) (*it)->Update();
	plConvict->Update();
}

void MainGameScene::LateUpdate()
{
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) {
		if ((*it)->Intersect(plConvict->GetCol())) {
			if (INPUT->KeyDown('E')) {
				(*it)->OpenTheChest();
				plConvict->GetFromChest((*it)->GetItemType());
				break;
			}
		}
	}
}

void MainGameScene::Render()
{
	map->Render();
	gui->Render();
	for (auto it = chestVector.begin(); it != chestVector.end(); it++) (*it)->Render();
	plConvict->Render();

}

void MainGameScene::ResizeScreen()
{
}
