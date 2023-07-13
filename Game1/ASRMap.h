#pragma once


struct RECTRange {
	Int2 rrVertex[4];
	float rrWidth;
	float rrHeight;
	/*RECTRange(Int2 maxVertex, Int2 minVertex) {
		rrVertex[0].x = minVertex.x;
		rrVertex[0].y = minVertex.y;

		rrVertex[1].x = minVertex.x;
		rrVertex[1].y = maxVertex.y;

		rrVertex[2].x = maxVertex.x;
		rrVertex[2].y = minVertex.y;

		rrVertex[3].x = maxVertex.x;
		rrVertex[3].y = maxVertex.y;

		rrWidth = maxVertex.x - minVertex.x + 1;
		rrHeight = maxVertex.y - minVertex.y + 1;
	}*/
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
	Int2 maxMapTilePos;
	Int2 minMapTilePos;

	ObRect* crossX;
	ObRect* crossY;

	ObTileMap* asrMap;
	BSPT* bspTree;
	BSPT* rootTree;
	vector<BSPT*> bspTreeVector;
	vector<BSPT*> realMapVector;

	int depth;
	int keyCount;

	bool isWH;
private:
	void DivideTree(Int2 maxPoint, Int2 minPoint, int Depth);
	void DeleteTree();

public:
	ASRMap();
	~ASRMap();

	void Init();
	void Update();
	void Render();

	void AutoRenderMap();
	void VectorShow();
	void MappingBspTree();
};

