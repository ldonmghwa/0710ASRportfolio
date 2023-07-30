#pragma once
class MainGameScene : public Scene
{
private:
	ObTileMap* map;
	vector<class ASRChest*> chestVector;
	class GameGUI* gui;
	class Player* plConvict;
	vector<class Monster*> minionVector;
	float fadeout = 0.0f;

public:
	MainGameScene();
	~MainGameScene();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

