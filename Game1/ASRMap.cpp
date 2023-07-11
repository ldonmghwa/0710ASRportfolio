#include "stdafx.h"
#include "ASRMap.h"

ASRMap::ASRMap()
{
	asrMap = new ObTileMap();
	asrMap->file = "asrMap.txt";

	crossX = new ObRect();
	crossX->scale.x = 20000.0f;
	crossX->scale.y = 2.0f;
	crossX->color = Vector4(0.8f, 0.1f, 0.5f, 0.5f);
	crossY = new ObRect();
	crossY->scale.x = 2.0f;
	crossY->scale.y = 20000.0f;
	crossY->color = Vector4(0.1f, 0.8f, 0.5f, 0.5f);

	maxMapTilePos = Int2(200, 200);
	minMapTilePos = Int2(0, 0);
	asrMap->tileImages[0] = new ObImage(L"Tile.png");
	asrMap->tileImages[0]->maxFrame = Int2(8, 6);
	asrMap->tileImages[1] = nullptr;
	asrMap->tileImages[2] = nullptr;
	asrMap->tileImages[3] = nullptr;
	asrMap->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
}

ASRMap::~ASRMap()
{
	//
	//delete asrMap->tileImages[0];
	delete crossX;
	delete crossY;
	delete asrMap;
}

void ASRMap::Init()
{
	isWH = true;
	depth = 3;
	asrMap->scale.x = 5.0f;
	asrMap->scale.y = 5.0f;
	asrMap->ResizeTile(maxMapTilePos);
	asrMap->SetWorldPos(Vector2(-maxMapTilePos.x * asrMap->scale.x * 0.5f , -maxMapTilePos.y * asrMap->scale.y * 0.5f));
	
}

void ASRMap::Update()
{
	ImGui::Text("cam pos: %f, %f", CAM->position.x, CAM->position.y);
	if (ImGui::Button("Cross line visible")) {
		crossX->isVisible = not crossX->isVisible;
		crossY->isVisible = not crossY->isVisible;
	}
	if (ImGui::Button("save")) {
		asrMap->Save();
	}
	asrMap->Update();
	crossX->Update();
	crossY->Update();
}

void ASRMap::Render()
{
	asrMap->Render();
	crossX->Render();
	crossY->Render();
}

void ASRMap::AutoRenderMap()
{
	bspTree = new BSPT(maxMapTilePos, minMapTilePos);
	
	//세로로 나누기
	if (RANDOM->Int(0, 99) < 50) {
		float divideRate = RANDOM->Int(4, 6) / 10.0f;
		DivideTree(Int2(maxMapTilePos.x * divideRate, maxMapTilePos.y), Int2(maxMapTilePos.x * divideRate, minMapTilePos.y)
			, maxMapTilePos, minMapTilePos);
		
	}
	//가로로 나누기
	else {
	}
	

}

void ASRMap::DivideTree(Int2 maxSplitPoint, Int2 minSplitPoint, Int2 maxPoint, Int2 minPoint)
{
	if (depth == 0) return;
	bspTree->left = new BSPT(maxSplitPoint, minPoint);
	bspTree = bspTree->left;
	//가로 분할
	if (isWH) {
	}
	bspTree->right = new BSPT(maxPoint, minSplitPoint);

}


