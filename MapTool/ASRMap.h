#pragma once
//#define TILENONEINT2 Int2(7, 14) 
#define TILENONEINT2 Int2(2, 9) 
#define TILESANDINT2 Int2(7, 1)
#define TILEWALLPTINT2 Int2(0, 15)
#define TILEWALLPTLDINT2 Int2(0, 19)
#define TILEWALLPTRDINT2 Int2(5, 19)
#define TILEWALLPTLUINT2 Int2(0, 14)
#define TILEWALLPTRUINT2 Int2(5, 14)
#define TILEWALLPTBTLINT2 Int2(0, 20)
#define TILEWALLPTBTINT2 Int2(1, 20)
#define TILEWALLPTBTRINT2 Int2(5, 20)
#define TILEOBSTPTRINT2 Int2(0, 0)
#define TILECHESTINT2 Int2(0, 7)

struct RANDOMRoom {
	Int2 vertex[2];
	Int2 middlePoint;
	Int2 wallPoint[3][2];
	vector<Int2> monsterSpawn;
};

struct RECTRange {
	Int2 rrVertex[4];
	RANDOMRoom room;
	float rrWidth;
	float rrHeight;
};

typedef struct BSPTree {
	int key;
	int depth;
	int parentKey;
	string leftOrRight;
	RECTRange value;
	struct BSPTree* left;
	struct BSPTree* right;
	BSPTree(Int2 maxVertex, Int2 minVertex, int _key, int _depth) {
		depth = _depth;
		leftOrRight = "root";
		parentKey = 0;
		key = _key;
		left = { NULL };
		right = { NULL };

		value.rrVertex[0].x = minVertex.x;
		value.rrVertex[0].y = minVertex.y;

		value.rrVertex[1].x = minVertex.x;
		value.rrVertex[1].y = maxVertex.y;

		value.rrVertex[2].x = maxVertex.x;
		value.rrVertex[2].y = minVertex.y;

		value.rrVertex[3].x = maxVertex.x;
		value.rrVertex[3].y = maxVertex.y;

		if (maxVertex.x - minVertex.x > maxVertex.y - minVertex.y) {
			if (RANDOM->Int(0, 99) < 50) {
				value.room.vertex[0].x = minVertex.x + 1;
				value.room.vertex[1].x = maxVertex.x - RANDOM->Int(4, 6);
			}
			else {
				value.room.vertex[0].x = minVertex.x + RANDOM->Int(4, 6);
				value.room.vertex[1].x = maxVertex.x - 1;
			}

			if (RANDOM->Int(0, 99) < 50) {
				value.room.vertex[0].y = minVertex.y + 1;
				value.room.vertex[1].y = maxVertex.y - RANDOM->Int(4, 6);
			}
			else {
				value.room.vertex[0].y = minVertex.y + RANDOM->Int(4, 6);
				value.room.vertex[1].y = maxVertex.y - 1;
			}
		}
		else {
			if (RANDOM->Int(0, 99) < 50) {
				value.room.vertex[0].x = minVertex.x + 1;
				value.room.vertex[1].x = maxVertex.x - RANDOM->Int(4, 6);
			}
			else {
				value.room.vertex[0].x = minVertex.x + RANDOM->Int(4, 6);
				value.room.vertex[1].x = maxVertex.x - 1;

			}

			if (RANDOM->Int(0, 99) < 50) {
				value.room.vertex[0].y = minVertex.y + 1;
				value.room.vertex[1].y = maxVertex.y - RANDOM->Int(4, 6);
			}
			else {
				value.room.vertex[0].y = minVertex.y + RANDOM->Int(4, 6);
				value.room.vertex[1].y = maxVertex.y - 1;
			}
		}
		

		value.room.middlePoint.x = (value.room.vertex[0].x + value.room.vertex[1].x) / 2;
		value.room.middlePoint.y = (value.room.vertex[0].y + value.room.vertex[1].y) / 2;
		//가로 > 세로
		if (value.room.vertex[1].x - value.room.vertex[0].x > value.room.vertex[1].y - value.room.vertex[0].y) {
			//큰방일때
			if(value.room.vertex[1].x - value.room.vertex[0].x> 20
				and value.room.vertex[1].y - value.room.vertex[0].y > 15){
				value.room.wallPoint[0][0].x = value.room.vertex[0].x + RANDOM->Int(3, 4);
				value.room.wallPoint[0][1].x = value.room.wallPoint[0][0].x + 4;
				value.room.wallPoint[1][0].x = value.room.vertex[1].x - 6;
				value.room.wallPoint[1][1].x = value.room.wallPoint[1][0].x + 4;
				value.room.wallPoint[2][0].x = value.room.middlePoint.x - 2;
				value.room.wallPoint[2][1].x = value.room.wallPoint[2][0].x + 4;

				value.room.wallPoint[0][1].y = value.room.vertex[1].y - RANDOM->Int(3, 4);
				value.room.wallPoint[0][0].y = value.room.wallPoint[0][1].y - 2;	
				value.room.wallPoint[1][1].y = value.room.vertex[1].y - RANDOM->Int(3, 4);
				value.room.wallPoint[1][0].y = value.room.wallPoint[1][1].y - 2;	
				value.room.wallPoint[2][0].y = value.room.vertex[0].y + RANDOM->Int(3, 4);
				value.room.wallPoint[2][1].y = value.room.wallPoint[2][0].y + 2;

				value.room.monsterSpawn.push_back(Int2(value.room.middlePoint.x, value.room.vertex[1].y - 2));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[0].x + 2, value.room.vertex[0].y + 2));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[1].x - 2, value.room.vertex[0].y + 2));
			}
			//작은방일때
			else {
				value.room.wallPoint[0][0].x = value.room.vertex[0].x + RANDOM->Int(2, 3);
				value.room.wallPoint[0][1].x = value.room.wallPoint[0][0].x + 3;
				value.room.wallPoint[1][0].x = value.room.vertex[1].x - 5;
				value.room.wallPoint[1][1].x = value.room.wallPoint[1][0].x + 3;
				value.room.wallPoint[2][0].x = value.room.middlePoint.x - 2;
				value.room.wallPoint[2][1].x = value.room.wallPoint[2][0].x + 3;

				value.room.wallPoint[0][1].y = value.room.vertex[1].y - 2;
				value.room.wallPoint[0][0].y = value.room.wallPoint[0][1].y - 1;
				value.room.wallPoint[1][1].y = value.room.vertex[1].y - 2;
				value.room.wallPoint[1][0].y = value.room.wallPoint[1][1].y - 1;
				value.room.wallPoint[2][0].y = value.room.vertex[0].y + 3;
				value.room.wallPoint[2][1].y = value.room.wallPoint[2][0].y + 1;

				value.room.monsterSpawn.push_back(Int2(value.room.middlePoint.x, value.room.vertex[1].y - 1));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[0].x + 1, value.room.vertex[0].y + 1));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[1].x - 1, value.room.vertex[0].y + 1));
			}
		}
		//세로 > 가로
		else {
			//큰방일 때 
			if (value.room.vertex[1].x - value.room.vertex[0].x > 15
				and value.room.vertex[1].y - value.room.vertex[0].y > 20) {
				value.room.wallPoint[0][0].x = value.room.vertex[0].x + RANDOM->Int(3, 4);
				value.room.wallPoint[0][1].x = value.room.wallPoint[0][0].x + 2;
				value.room.wallPoint[1][1].x = value.room.vertex[1].x - RANDOM->Int(3, 4);
				value.room.wallPoint[1][0].x = value.room.wallPoint[1][1].x - 2;
				value.room.wallPoint[2][1].x = value.room.vertex[1].x - RANDOM->Int(3, 4);
				value.room.wallPoint[2][0].x = value.room.wallPoint[2][1].x - 2;

				value.room.wallPoint[0][0].y = value.room.middlePoint.y - 2;
				value.room.wallPoint[0][1].y = value.room.wallPoint[0][0].y + 4;
				value.room.wallPoint[1][0].y = value.room.vertex[0].y + RANDOM->Int(3, 4);
				value.room.wallPoint[1][1].y = value.room.wallPoint[1][0].y + 4;
				value.room.wallPoint[2][0].y = value.room.vertex[1].y - 6;
				value.room.wallPoint[2][1].y = value.room.wallPoint[2][0].y + 4;

				value.room.monsterSpawn.push_back(Int2(value.room.vertex[0].x + 2, value.room.middlePoint.y));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[1].x - 2, value.room.vertex[0].y + 2));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[1].x - 2, value.room.vertex[1].y - 2));
			}
			else {
				value.room.wallPoint[0][0].x = value.room.vertex[0].x + RANDOM->Int(2, 3);
				value.room.wallPoint[0][1].x = value.room.wallPoint[0][0].x + 1;
				value.room.wallPoint[1][1].x = value.room.vertex[1].x - 2;
				value.room.wallPoint[1][0].x = value.room.wallPoint[1][1].x - 1;
				value.room.wallPoint[2][1].x = value.room.vertex[1].x - 2;
				value.room.wallPoint[2][0].x = value.room.wallPoint[2][1].x - 1;

				value.room.wallPoint[0][0].y = value.room.middlePoint.y - 1;
				value.room.wallPoint[0][1].y = value.room.wallPoint[0][0].y + 3;
				value.room.wallPoint[1][0].y = value.room.vertex[0].y + RANDOM->Int(3, 4);
				value.room.wallPoint[1][1].y = value.room.wallPoint[1][0].y + 3;
				value.room.wallPoint[2][0].y = value.room.vertex[1].y - 5;
				value.room.wallPoint[2][1].y = value.room.wallPoint[2][0].y + 3;

				value.room.monsterSpawn.push_back(Int2(value.room.vertex[0].x + 1, value.room.middlePoint.y));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[1].x - 1, value.room.vertex[0].y + 1));
				value.room.monsterSpawn.push_back(Int2(value.room.vertex[1].x - 1, value.room.vertex[1].y - 1));
			}
			
		}
		value.rrWidth = maxVertex.x - minVertex.x + 1;
		value.rrHeight = maxVertex.y - minVertex.y + 1;
	}
}BSPT;
typedef struct BSPTPointer {
	struct BSPTree* prev;
	struct BSPTree* next;
}BSPTP;


class ASRMap
{
private:
	Int2 minMapTilePos;

	ObRect* crossX;
	ObRect* crossY;

	ObTileMap* asrMap;
	BSPT* bspTree;
	BSPT* rootTree;
	vector<BSPT*> bspTreeVector;
	vector<BSPT*> realMapVector;
	vector<class Tile*> way;

	int keyCount;
	int tileDegreeOfFall;
	int tileImgIdx;

	//ObIso*		isoMap;
	Int2		tileSize;
	ObRect*		LineX, *LineY;
	int			brushImgIdx;
	Int2		brushFrame;
	int			brushState;
	Color		brushColor;


	bool isWH;
private:
	void DivideTree(Int2 maxPoint, Int2 minPoint, int Depth);
	void DeleteTree();
	void SearchAroundWay(Int2 tempTilePos);
public:
	Int2 maxMapTilePos;
	int depth;
	int bossRoomIdx;
	int stepIdx;
	int count;
public:
	ASRMap();
	~ASRMap();

	void Init();
	void Update();
	void Render();

	void ResizeTileXY(){
		asrMap->ResizeTile(Int2(maxMapTilePos.x + 1, maxMapTilePos.y + 1));
		asrMap->SetWorldPos(Vector2(-maxMapTilePos.x * asrMap->scale.x * 0.5f, -maxMapTilePos.y * asrMap->scale.y * 0.5f));
		asrMap->CreateTileCost();
		if (bspTree) {
			delete bspTree;
			bspTree = nullptr;
		}
		bspTree = new BSPT(maxMapTilePos, minMapTilePos, keyCount, depth);
		rootTree = bspTree;
	}
	void AutoRenderMap();
	void StepRederMap();
	void VectorShow();
	void MappingBspTree();
};

