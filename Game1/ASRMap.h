#pragma once


struct RECTRange {
	Int2 rrVertex[4];
	float rrWidth;
	float rrHeight;
	RECTRange(Int2 maxVertex, Int2 minVertex) {
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
	}
};
typedef struct BSPTree {
	RECTRange value;
	BSPTree* left;
	BSPTree* right;
}BSPT;

class ASRMap
{
private:
	Int2 maxMapTileSize;
	Int2 minMapTileSize;
	map<int, RECTRange*> mRR;
	ObTileMap* asrMap;
	BSPT* bspTree;
public:
	ASRMap();
	~ASRMap();

	void Init();
	void Update();
	void Render();

	void AutoRenderMap();
	void DivideTree(int maxKey, int minKey, int centerKey);
};

