#include "stdafx.h"
#include "ASRMap.h"

ASRMap::ASRMap()
{
	asrMap = new ObTileMap();
	asrMap->file = "asrMap.txt";

	maxMapTileSize = Int2(200, 200);
	minMapTileSize = Int2(0, 0);
	asrMap->tileImages[0] = new ObImage(L"Tile.png");
	asrMap->tileImages[0]->maxFrame = Int2(8, 6);
	asrMap->tileImages[1] = nullptr;
	asrMap->tileImages[2] = nullptr;
	asrMap->tileImages[3] = nullptr;
	asrMap->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	bspTree = { NULL };
}

ASRMap::~ASRMap()
{
	//asrMap->Save();
	//TEXTURE->DeleteTexture(L"Tile.png");
	delete asrMap->tileImages[0];
	delete asrMap;
}

void ASRMap::Init()
{

	asrMap->scale.x = 50.0f;
	asrMap->scale.y = 50.0f;
	asrMap->ResizeTile(maxMapTileSize);
	asrMap->SetWorldPos(Vector2(-200.0f, -200.0f));
}

void ASRMap::Update()
{
	asrMap->Update();
}

void ASRMap::Render()
{
	asrMap->Render();
}

void ASRMap::AutoRenderMap()
{
	mRR.clear();
	bool isHeight = true;

	int minKey = 0;
	int maxKey = 14;
	int centerKey = 7;
	mRR.insert(make_pair(centerKey, new RECTRange(maxMapTileSize, minMapTileSize)));
	DivideTree(centerKey - 1, minKey, centerKey);

	auto it = mRR.begin();

}

void ASRMap::DivideTree(int maxKey, int minKey, int centerKey)
{
	if ((maxKey + minKey) / 2 < centerKey) {
		centerKey = (maxKey + minKey) / 2;
		DivideTree(maxKey / 2, minKey, centerKey);
	}
}


