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

	maxMapTilePos = Int2(100, 100);
	minMapTilePos = Int2(0, 0);
	asrMap->tileImages[0] = new ObImage(L"Tile.png");
	asrMap->tileImages[0]->maxFrame = Int2(8, 6);
	asrMap->tileImages[1] = new ObImage(L"Tile1.png");
	asrMap->tileImages[1]->maxFrame = Int2(12, 21); 
	asrMap->tileImages[2] = new ObImage(L"atlas0_412.png");
	asrMap->tileImages[2]->maxFrame = Int2(12, 21);
	asrMap->tileImages[3] = nullptr;
	asrMap->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
}

ASRMap::~ASRMap()
{
	DeleteTree();
	delete crossX;
	delete crossY;
	delete asrMap;
	//delete bspTree;
}

void ASRMap::Init()
{
	keyCount = 0;
	isWH = RANDOM->Int(0, 99) < 50 ? true : false;
	depth = 2;
	count = 0;
	tileDegreeOfFall = 1;
	asrMap->scale.x = 5.0f;
	asrMap->scale.y = 5.0f;
	asrMap->ResizeTile(Int2(maxMapTilePos.x + 1, maxMapTilePos.y + 1));
	asrMap->SetWorldPos(Vector2(-maxMapTilePos.x * asrMap->scale.x * 0.5f, -maxMapTilePos.y * asrMap->scale.y * 0.5f));
	asrMap->CreateTileCost();
	bspTree = new BSPT(maxMapTilePos, minMapTilePos, keyCount, depth);
	rootTree = bspTree;
	bossRoomIdx = 1;
	for (int i = 0; i < depth - 1; i++) {
		bossRoomIdx *= 2;
	};
	bossRoomIdx -= 1;
	tileImgIdx = 0;
	brushImgIdx = 2;
}

void ASRMap::Update()
{
	//ImGui::Text("cam pos: %f, %f", CAM->position.x, CAM->position.y);
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
	system("cls");
	isWH = RANDOM->Int(0, 99) < 50 ? true : false;
	bspTree = rootTree;
	bspTreeVector.clear();
	bspTreeVector.reserve(pow(2, depth));
	realMapVector.clear();
	realMapVector.reserve(pow(2, depth - 1));
	bspTreeVector.push_back(bspTree);
	DivideTree(maxMapTilePos, minMapTilePos, depth);
	VectorShow();
	MappingBspTree();
}

void ASRMap::StepRederMap()
{
	if (count == 1) {
		system("cls");
		isWH = RANDOM->Int(0, 99) < 50 ? true : false;
		bspTree = rootTree;
		bspTreeVector.clear();
		bspTreeVector.reserve(pow(2, depth));
		realMapVector.clear();
		realMapVector.reserve(pow(2, depth - 1));
		bspTreeVector.push_back(bspTree);
		DivideTree(maxMapTilePos, minMapTilePos, depth);
	}
	if (stepIdx == 0) {
		auto bspit = bspTreeVector.begin();
		//전체 배경 타일 매핑
		for (int i = (*bspit)->value.rrVertex[0].y; i < (*bspit)->value.rrVertex[3].y + 1; i++) {
			for (int j = (*bspit)->value.rrVertex[0].x; j < (*bspit)->value.rrVertex[3].x + 1; j++) {
				asrMap->SetTile(0, Int2(j, i), TILENONEINT2, brushImgIdx, TILE_NONE, Color(0.5f, 0.5f, 0.5f, 0.5f));
			}
		}
		asrMap->UpdateSetTile();
	}
	else if (stepIdx == 1) {
		//방 타일 매핑
		for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
			//세로 y값
			for (int i = (*it)->value.room.vertex[0].y + 1; i < (*it)->value.room.vertex[1].y; i++) {
				//가로 x값
				for (int j = (*it)->value.room.vertex[0].x; j < (*it)->value.room.vertex[1].x; j++) {
					asrMap->SetTile(0, Int2(j, i), TILESANDINT2, brushImgIdx, TILE_SAND, Color(0.5f, 0.5f, 0.5f, 0.5f));
				}
			}
		}
		asrMap->UpdateSetTile();
	}
	else if (stepIdx == 2) {
		//방 사이의 길 매핑
		for (int i = 0; i + 1 < realMapVector.size(); i++) {
			Int2 startPos = realMapVector[i]->value.room.middlePoint;
			Int2 destPos = realMapVector[i + 1]->value.room.middlePoint;
			asrMap->PathFinding(startPos, destPos, way);
			cout << "- " << i << "~" << i + 1 << " way: ";
			for (int j = 0; j + 1 < way.size(); j++) {
				Int2 tempTilePos;
				cout << "[" << way[j]->Pos.x << ", " << way[j]->Pos.y << "] ";
				asrMap->WorldPosToTileIdx(way[j]->Pos, tempTilePos);
				asrMap->SetTile(0, tempTilePos, TILESANDINT2, brushImgIdx, TILE_SAND, Color(0.5f, 0.5f, 0.5f, 0.5f));
				SearchAroundWay(tempTilePos);
			}
			cout << endl << endl;
		}
		asrMap->UpdateSetTile();
		
	}
	else if (stepIdx == 3) {
		//방안의 장애물 매핑
		for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
			for (int k = 0; k < 3; k++) {
				for (int i = (*it)->value.room.wallPoint[k][0].y; i < (*it)->value.room.wallPoint[k][1].y; i++) {
					for (int j = (*it)->value.room.wallPoint[k][0].x; j < (*it)->value.room.wallPoint[k][1].x; j++) {
						asrMap->SetTile(0, Int2(j, i), TILEOBSTPTRINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
					}
				}
			}
		}
		asrMap->UpdateSetTile();
	}
	else if (stepIdx == 4) {
		//길 주변 벽 매핑
		for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
			//세로 y값
			for (int i = (*it)->value.room.vertex[0].y - 1; i < (*it)->value.room.vertex[1].y + 1; i++) {
				//가로 x값
				for (int j = (*it)->value.room.vertex[0].x - 1; j < (*it)->value.room.vertex[1].x + 1; j++) {
					if (i == (*it)->value.room.vertex[0].y - 1) {
						if (asrMap->GetTileState(Int2(j, i)) == TILE_NONE) {

							if (j == (*it)->value.room.vertex[0].x - 1) {
								asrMap->SetTile(0, Int2(j, i), TILEWALLPTBTLINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
							}
							else if (j == (*it)->value.room.vertex[1].x) {
								asrMap->SetTile(0, Int2(j, i), TILEWALLPTBTRINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
							}
							else asrMap->SetTile(0, Int2(j, i), TILEWALLPTBTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						}
					}
					else if (i == (*it)->value.room.vertex[0].y
						or j == (*it)->value.room.vertex[0].x - 1
						or i == (*it)->value.room.vertex[1].y
						or j == (*it)->value.room.vertex[1].x)
					{
						if (asrMap->GetTileState(Int2(j, i)) == TILE_NONE) {
							asrMap->SetTile(0, Int2(j, i), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
							if (i == (*it)->value.room.vertex[0].y and j == (*it)->value.room.vertex[0].x - 1)
								asrMap->SetTile(0, Int2(j, i), TILEWALLPTLDINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
							if (i == (*it)->value.room.vertex[0].y and j == (*it)->value.room.vertex[1].x)
								asrMap->SetTile(0, Int2(j, i), TILEWALLPTRDINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
							if (i == (*it)->value.room.vertex[1].y and j == (*it)->value.room.vertex[0].x - 1)
								asrMap->SetTile(0, Int2(j, i), TILEWALLPTLUINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
							if (i == (*it)->value.room.vertex[1].y and j == (*it)->value.room.vertex[1].x)
								asrMap->SetTile(0, Int2(j, i), TILEWALLPTRUINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

						}
					}
				}
			}
		}
		asrMap->UpdateSetTile();
	}
	else if (stepIdx == 5) {
		for (int k = 0; k < realMapVector.size(); k++) {
			if (k != bossRoomIdx) {
				for (int i = realMapVector[k]->value.room.vertex[0].y - 1;
					i < realMapVector[k]->value.room.vertex[1].y + 1; i++) {
					for (int j = realMapVector[k]->value.room.vertex[0].x - 1;
						j < realMapVector[k]->value.room.vertex[1].x + 1; j++) {
						for (auto it2 = realMapVector[k]->value.room.monsterSpawn.begin();
							it2 != realMapVector[k]->value.room.monsterSpawn.end(); it2++) {
							if ((*it2).x == j and (*it2).y == i) {
								asrMap->SetTile(
									0,
									Int2(j, i),
									TILESANDINT2,
									brushImgIdx,
									TILE_MSPAWN,
									Color(1.0f, 0.0f, 0.0f, 0.5f));
							}
						}
					}
				}
			}
		}
		asrMap->UpdateSetTile();
	}
	else if (stepIdx == 6) {
		//상자 매핑
		for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
			if (RANDOM->Int(0, 99) < 100)
				asrMap->SetTile(0,
					Int2((*it)->value.room.middlePoint.x, (*it)->value.room.middlePoint.y),
					TILECHESTINT2,
					brushImgIdx,
					TILE_TRAP,
					Color(0.5f, 0.5f, 0.5f, 0.5f));
		}
		asrMap->UpdateSetTile();
	}
	else if (stepIdx == 7) {
		//보스 스폰위치 매핑
		asrMap->SetTile(
			0,
			Int2(realMapVector[bossRoomIdx]->value.room.middlePoint.x - 1,
				realMapVector[bossRoomIdx]->value.room.vertex[1].y - 6),
			TILESANDINT2,
			brushImgIdx,
			TILE_MBSPAWN,
			Color(0.0f, 1.0f, 0.0f, 0.5f)
		);
		//플레이어 버튼 스폰위치 매핑
		asrMap->SetTile(
			0,
			Int2(realMapVector[bossRoomIdx]->value.room.middlePoint.x - 1,
				realMapVector[bossRoomIdx]->value.room.vertex[0].y + 2),
			TILESANDINT2,
			brushImgIdx,
			TILE_PSPAWNB,
			Color(0.0f, 1.0f, 1.0f, 0.5f)
		);
		//플레이어 스폰위치 매핑
		asrMap->SetTile(
			0,
			Int2(realMapVector[0]->value.room.middlePoint.x - 1,
				realMapVector[0]->value.room.middlePoint.y - 1),
			TILESANDINT2,
			brushImgIdx,
			TILE_PSPAWN,
			Color(0.0f, 0.0f, 1.0f, 0.5f)
		);
		asrMap->UpdateSetTile();
	}
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
	//전체 배경 타일 매핑
	for (int i = (*bspit)->value.rrVertex[0].y; i < (*bspit)->value.rrVertex[3].y + 1; i++) {
		for (int j = (*bspit)->value.rrVertex[0].x; j < (*bspit)->value.rrVertex[3].x + 1; j++) {
			asrMap->SetTile(0, Int2(j, i), TILENONEINT2, brushImgIdx, TILE_NONE, Color(0.5f, 0.5f, 0.5f, 0.5f));
		}
	}
	//방 사이의 길 매핑
	for (int i = 0; i + 1 < realMapVector.size(); i++) {
		Int2 startPos = realMapVector[i]->value.room.middlePoint;
		Int2 destPos = realMapVector[i + 1]->value.room.middlePoint;
		asrMap->PathFinding(startPos, destPos, way);
		cout << "- " << i << "~" << i + 1 << " way: ";
		for (int j = 0; j + 1 < way.size(); j++) {
			Int2 tempTilePos;
			cout << "[" << way[j]->Pos.x << ", " << way[j]->Pos.y << "] ";
			asrMap->WorldPosToTileIdx(way[j]->Pos, tempTilePos);
			asrMap->SetTile(0, tempTilePos, TILESANDINT2, brushImgIdx, TILE_SAND, Color(0.5f, 0.5f, 0.5f, 0.5f));
			SearchAroundWay(tempTilePos);
		}
		cout << endl << endl;
	}
	//방 타일 매핑
	for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
		//세로 y값
		for (int i = (*it)->value.room.vertex[0].y + 1; i < (*it)->value.room.vertex[1].y; i++) {
			//가로 x값
			for (int j = (*it)->value.room.vertex[0].x; j < (*it)->value.room.vertex[1].x; j++) {
				asrMap->SetTile(0, Int2(j, i), TILESANDINT2, brushImgIdx, TILE_SAND, Color(0.5f, 0.5f, 0.5f, 0.5f));
			}
		}
		//상자 위치 매핑
		if (RANDOM->Int(0, 99) < 100)
			asrMap->SetTile(0,
				Int2((*it)->value.room.middlePoint.x, (*it)->value.room.middlePoint.y),
				TILECHESTINT2,
				brushImgIdx,
				TILE_TRAP,
				Color(0.5f, 0.5f, 0.5f, 0.5f));
	}
	//방안의 장애물 매핑
	for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
		for (int k = 0; k < 3; k++) {
			for (int i = (*it)->value.room.wallPoint[k][0].y; i < (*it)->value.room.wallPoint[k][1].y; i++) {
				for (int j = (*it)->value.room.wallPoint[k][0].x; j < (*it)->value.room.wallPoint[k][1].x; j++) {
					asrMap->SetTile(0, Int2(j, i), TILEOBSTPTRINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
				}
			}
		}
	}
	//길 주변 벽 매핑
	for (auto it = realMapVector.begin(); it != realMapVector.end(); it++) {
		//세로 y값
		for (int i = (*it)->value.room.vertex[0].y - 1; i < (*it)->value.room.vertex[1].y + 1; i++) {
			//가로 x값
			for (int j = (*it)->value.room.vertex[0].x - 1; j < (*it)->value.room.vertex[1].x + 1; j++) {
				if (i == (*it)->value.room.vertex[0].y - 1) {
					if (asrMap->GetTileState(Int2(j, i)) == TILE_NONE) {
						
						if (j == (*it)->value.room.vertex[0].x - 1) {
							asrMap->SetTile(0, Int2(j, i), TILEWALLPTBTLINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						}
						else if (j == (*it)->value.room.vertex[1].x) {
							asrMap->SetTile(0, Int2(j, i), TILEWALLPTBTRINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						}else asrMap->SetTile(0, Int2(j, i), TILEWALLPTBTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
					}
				}
				else if (i == (*it)->value.room.vertex[0].y
					or j == (*it)->value.room.vertex[0].x - 1
					or i == (*it)->value.room.vertex[1].y
					or j == (*it)->value.room.vertex[1].x) 
				{
					if (asrMap->GetTileState(Int2(j, i)) == TILE_NONE) {
						asrMap->SetTile(0, Int2(j, i), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						if (i == (*it)->value.room.vertex[0].y and j == (*it)->value.room.vertex[0].x - 1)
							asrMap->SetTile(0, Int2(j, i), TILEWALLPTLDINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						if (i == (*it)->value.room.vertex[0].y and j == (*it)->value.room.vertex[1].x)
							asrMap->SetTile(0, Int2(j, i), TILEWALLPTRDINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						if (i == (*it)->value.room.vertex[1].y and j == (*it)->value.room.vertex[0].x - 1)
							asrMap->SetTile(0, Int2(j, i), TILEWALLPTLUINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
						if (i == (*it)->value.room.vertex[1].y and j == (*it)->value.room.vertex[1].x)
							asrMap->SetTile(0, Int2(j, i), TILEWALLPTRUINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

					}
				}
			}
		}
	}
	for (int k = 0; k < realMapVector.size(); k++) {
		if (k != bossRoomIdx) {
			for (int i = realMapVector[k]->value.room.vertex[0].y - 1;
				i < realMapVector[k]->value.room.vertex[1].y + 1; i++) {
				for (int j = realMapVector[k]->value.room.vertex[0].x - 1;
					j < realMapVector[k]->value.room.vertex[1].x + 1; j++) {
					for (auto it2 = realMapVector[k]->value.room.monsterSpawn.begin();
						it2 != realMapVector[k]->value.room.monsterSpawn.end(); it2++) {
						if ((*it2).x == j and (*it2).y == i) {
							asrMap->SetTile(
								0,
								Int2(j, i),
								TILESANDINT2,
								brushImgIdx,
								TILE_MSPAWN,
								Color(1.0f, 0.0f, 0.0f, 0.5f));
						}
					}
				}
			}
		}
	}
	
	//보스 스폰위치 매핑
	asrMap->SetTile(
		0,
		Int2(realMapVector[bossRoomIdx]->value.room.middlePoint.x - 1,
			realMapVector[bossRoomIdx]->value.room.vertex[1].y - 6),
		TILESANDINT2,
		brushImgIdx,
		TILE_MBSPAWN,
		Color(0.0f, 1.0f, 0.0f, 0.5f)
	);
	//플레이어 버튼 스폰위치 매핑
	asrMap->SetTile(
		0,
		Int2(realMapVector[bossRoomIdx]->value.room.middlePoint.x - 1,
			realMapVector[bossRoomIdx]->value.room.vertex[0].y + 2),
		TILESANDINT2,
		brushImgIdx,
		TILE_PSPAWNB,
		Color(0.0f, 1.0f, 1.0f, 0.5f)
	);
	//플레이어 스폰위치 매핑
	asrMap->SetTile(
		0,
		Int2(realMapVector[0]->value.room.middlePoint.x - 1,
			realMapVector[0]->value.room.middlePoint.y - 1),
		TILESANDINT2,
		brushImgIdx,
		TILE_PSPAWN,
		Color(0.0f, 0.0f, 1.0f, 0.5f)
	);
	asrMap->UpdateSetTile();
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
	if (bspTree->value.rrWidth > bspTree->value.rrHeight) {
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
		if (bspTree->value.rrWidth > bspTree->value.rrHeight) {
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
	for (auto it = bspTreeVector.begin(); it != bspTreeVector.end(); it++) {
		delete (*it);
	}
}

void ASRMap::SearchAroundWay(Int2 tempTilePos)
{
	if (asrMap->GetTileState(Int2(tempTilePos.x + 1, tempTilePos.y)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x + 1, tempTilePos.y), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

	if (asrMap->GetTileState(Int2(tempTilePos.x + 1, tempTilePos.y + 1)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x + 1, tempTilePos.y + 1), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

	if (asrMap->GetTileState(Int2(tempTilePos.x, tempTilePos.y + 1)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x, tempTilePos.y + 1), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

	if (asrMap->GetTileState(Int2(tempTilePos.x - 1, tempTilePos.y + 1)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x - 1, tempTilePos.y + 1), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

	if (asrMap->GetTileState(Int2(tempTilePos.x - 1, tempTilePos.y)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x - 1, tempTilePos.y), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

	if (asrMap->GetTileState(Int2(tempTilePos.x - 1, tempTilePos.y - 1)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x - 1, tempTilePos.y - 1), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

	if (asrMap->GetTileState(Int2(tempTilePos.x, tempTilePos.y - 1)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x, tempTilePos.y - 1), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));

	if (asrMap->GetTileState(Int2(tempTilePos.x + 1, tempTilePos.y - 1)) == TILE_NONE)
		asrMap->SetTile(0, Int2(tempTilePos.x + 1, tempTilePos.y - 1), TILEWALLPTINT2, brushImgIdx, TILE_WALL, Color(0.5f, 0.5f, 0.5f, 0.5f));
}


