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
	keyCount = 0;
	isWH = true;
	depth = 3;
	asrMap->scale.x = 5.0f;
	asrMap->scale.y = 5.0f;
	asrMap->ResizeTile(maxMapTilePos);
	asrMap->SetWorldPos(Vector2(-maxMapTilePos.x * asrMap->scale.x * 0.5f, -maxMapTilePos.y * asrMap->scale.y * 0.5f));
	bspTree = new BSPT(maxMapTilePos, minMapTilePos, keyCount);
	top = bspTree;

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
	bspTreeVector.clear();
	bspTreeVector.reserve(15);
	bspTreeVector.push_back(bspTree);
	DivideTree(maxMapTilePos, minMapTilePos, 4);
	BSPTreeVectorShow();
}



void ASRMap::DivideTree(Int2 maxPoint, Int2 minPoint, int Depth)
{
	Depth--;
	if (Depth <= 0) return;
	keyCount++;
	float divideRate = RANDOM->Int(4, 5) / 10.0f;
	Int2 temp;
	//세로
	if (RANDOM->Int(0, 99) < 50) {
		temp.x = (maxPoint.x - minPoint.x) * divideRate + minPoint.x;
		temp.y = maxPoint.y;
	}
	//가로
	else {
		temp.x = maxPoint.x;
		temp.y = (maxPoint.y - minPoint.y) * divideRate + minPoint.y;
	}
	bspTree->left = new BSPT(temp, minPoint, keyCount);
	bspTreeVector.push_back(bspTree->left);
	bspTree->front = bspTree;
	cout << "left - depth: " << Depth << " | current key: " << keyCount << " | front key: " << bspTree->front->key
		<< " | maxPoint: " << temp.x << ", " << temp.y
		<< " | minPoint: " << minPoint.x << ", " << minPoint.y << endl;
	bspTree = bspTree->left;
	DivideTree(temp, minPoint, Depth);
	bspTree = bspTree->front;

	keyCount++;
	Int2 temp2;
	//divideRate = RANDOM->Int(4, 6) / 10.0f;
	if (RANDOM->Int(0, 99) < 50) {
		temp2.x = (maxPoint.x - minPoint.x) * divideRate + minPoint.x;
		temp2.y = minPoint.y;
	}
	else {
		temp2.x = minPoint.x;
		temp2.y = (maxPoint.y - minPoint.y) * divideRate + minPoint.y;
	}
	bspTree->right = new BSPT(maxPoint, temp2, keyCount);
	bspTreeVector.push_back(bspTree->right);
	cout << "right - depth: " << Depth << " | current key: " << keyCount << " | front key: " << bspTree->front->key
		<< " | maxPoint: " << maxPoint.x << ", " << maxPoint.y
		<< " | minPoint: " << temp2.x << ", " << temp2.y << endl;
	bspTree = bspTree->right;
	DivideTree(maxPoint, temp2, Depth);

}


