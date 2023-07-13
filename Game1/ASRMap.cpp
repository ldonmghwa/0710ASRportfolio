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

	maxMapTilePos = Int2(200, 100);
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
	DeleteTree();
	delete crossX;
	delete crossY;
	delete asrMap;
	//delete bspTree;
}

void ASRMap::Init()
{
	keyCount = 0;
	isWH = true;
	depth = 5;
	asrMap->scale.x = 5.0f;
	asrMap->scale.y = 5.0f;
	asrMap->ResizeTile(Int2(maxMapTilePos.x + 1, maxMapTilePos.y + 1));
	asrMap->SetWorldPos(Vector2(-maxMapTilePos.x * asrMap->scale.x * 0.5f, -maxMapTilePos.y * asrMap->scale.y * 0.5f));
	bspTree = new BSPT(maxMapTilePos, minMapTilePos, keyCount, depth);
	rootTree = bspTree;
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
	bspTree = rootTree;
	bspTreeVector.clear();
	bspTreeVector.reserve(pow(2, depth));
	realMapVector.clear();
	realMapVector.reserve(pow(2, depth - 1));
	bspTreeVector.push_back(bspTree);
	DivideTree(maxMapTilePos, minMapTilePos, bspTree->depth);
	VectorShow();
	MappingBspTree();
}

void ASRMap::VectorShow()
{
	cout << "-BSPTreeVeCtor-" << endl;
	for (auto it = bspTreeVector.begin(); it != bspTreeVector.end(); it++) {
		cout << (*it)->leftOrRight
			<< " | key: " << (*it)->key << " | depth: " << (*it)->depth
			<< " | parent key: " << (*it)->parentKey
			<< " | maxPoint: " << (*it)->value.rrVertex[3].x << ", " << (*it)->value.rrVertex[3].y
			<< " | minPoint: " << (*it)->value.rrVertex[0].x << ", " << (*it)->value.rrVertex[0].y << endl;
	}
	cout << "-RealMapVeCtor-" << endl;
	for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
		cout << (*it)->leftOrRight
			<< " | key: " << (*it)->key << " | depth: " << (*it)->depth
			<< " | parent key: " << (*it)->parentKey
			<< " | maxPoint: " << (*it)->value.rrVertex[3].x << ", " << (*it)->value.rrVertex[3].y
			<< " | minPoint: " << (*it)->value.rrVertex[0].x << ", " << (*it)->value.rrVertex[0].y << endl;
	}
}

void ASRMap::MappingBspTree()
{
	auto bspit = bspTreeVector.begin();
	for (int i = (*bspit)->value.rrVertex[0].y; i < (*bspit)->value.rrVertex[3].y; i++) {
		for (int j = (*bspit)->value.rrVertex[0].x; j < (*bspit)->value.rrVertex[3].x + 1; j++) {
			/*if (i == (*bspit)->value.rrVertex[0].y) {
				asrMap->SetTile(Int2(j, i), Int2(7, 5), 0, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
			}
			else if (j == (*bspit)->value.rrVertex[0].x) {
				asrMap->SetTile(Int2(j, i), Int2(7, 5), 0, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
			}
			else if (i == (*bspit)->value.rrVertex[3].y - 1) {
				asrMap->SetTile(Int2(j, i), Int2(7, 5), 0, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
			}
			else if (j == (*bspit)->value.rrVertex[3].x) {
				asrMap->SetTile(Int2(j, i), Int2(7, 5), 0, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
			}
			else {*/
			asrMap->SetTile(Int2(j, i), Int2(1, 1), 0, TILE_NONE, Color(0.5f, 0.5f, 0.5f, 0.5f));
			//}
		}
	}


	for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
		//세로 y값
		for (int i = (*it)->value.rrVertex[0].y; i < (*it)->value.rrVertex[3].y + 1; i++) {
			//가로 x값
			for (int j = (*it)->value.rrVertex[0].x; j < (*it)->value.rrVertex[3].x + 1; j++) {
				if ((i >= (*it)->value.rrVertex[0].y + 2 and i <= (*it)->value.rrVertex[3].y - 2)
					and (j >= (*it)->value.rrVertex[0].x + 2 and j <= (*it)->value.rrVertex[3].x - 2)) {
					if (i == (*it)->value.rrVertex[0].y + 2
						or j == (*it)->value.rrVertex[0].x + 2
						or i == (*it)->value.rrVertex[3].y - 2
						or j == (*it)->value.rrVertex[3].x - 2) {
						asrMap->SetTile(Int2(j, i), Int2(7, 5), 0, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						/*}
						else if (j == (*it)->value.rrVertex[0].x + 2) {
							asrMap->SetTile(Int2(j, i), Int2(7, 5), 0, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						}
						else if (i == (*it)->value.rrVertex[3].y - 1 - 2) {
							asrMap->SetTile(Int2(j, i), Int2(7, 5), 0, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						}
						else if (j == (*it)->value.rrVertex[3].x - 2) {*/
					}
					else {
						asrMap->SetTile(Int2(j, i), Int2(5, 3), 0, TILE_NONE, Color(0.5f, 0.5f, 0.5f, 0.5f));
					}
				}
			}
		}
	}
}

void ASRMap::DivideTree(Int2 maxPoint, Int2 minPoint, int _depth)
{
	_depth--;
	if (_depth <= 0) return;
	BSPT* parent = bspTree;
	keyCount++;
	float divideRate = RANDOM->Int(4, 6) / 10.0f;
	Int2 temp;
	bool isLeftOrRight = RANDOM->Int(0, 99) < 50 ? true : false;
	//세로
	if (isLeftOrRight) {
		temp.x = (maxPoint.x - minPoint.x) * divideRate + minPoint.x;
		temp.y = maxPoint.y;
	}
	//가로
	else {
		temp.x = maxPoint.x;
		temp.y = (maxPoint.y - minPoint.y) * divideRate + minPoint.y;
	}
	bspTree->left = new BSPT(temp, minPoint, keyCount, _depth);
	bspTreeVector.push_back(bspTree->left);
	if (_depth == 1) realMapVector.push_back(bspTree->left);
	bspTree->left->parentKey = parent->key;
	bspTree->left->leftOrRight = "left";
	bspTree = bspTree->left;
	DivideTree(temp, minPoint, _depth);
	bspTree = parent;


	if (_depth >= 1) {
		keyCount++;
		Int2 temp2;
		//divideRate = RANDOM->Int(4, 6) / 10.0f;
		if (isLeftOrRight) {
			temp2.x = (maxPoint.x - minPoint.x) * divideRate + minPoint.x;
			temp2.y = minPoint.y;
		}
		else {
			temp2.x = minPoint.x;
			temp2.y = (maxPoint.y - minPoint.y) * divideRate + minPoint.y;
		}
		bspTree->right = new BSPT(maxPoint, temp2, keyCount, _depth);
		bspTreeVector.push_back(bspTree->right);
		if (_depth == 1) realMapVector.push_back(bspTree->right);
		bspTree->right->parentKey = bspTree->key;
		bspTree->right->leftOrRight = "right";
		bspTree = bspTree->right;
		DivideTree(maxPoint, temp2, _depth);
	}
}
void ASRMap::DeleteTree()
{
	for (auto it = bspTreeVector.begin(); it != bspTreeVector.end(); it++) delete (*it);
}


