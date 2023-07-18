#pragma once
#define HPMAX 5
#define HPBARMAX 3
enum HPBarState {
	FULL,
	HALF,
	ZERO
};
struct HPBar {
	ObImage* heartBar[HPBARMAX];
	int hpBarState;
	HPBar() {}
	~HPBar() {
		for (int i = 0; i < HPBARMAX; i++) delete heartBar[i];
	}
};

class MainGameScene : public Scene
{
private:
	ObTileMap* map;
	HPBar* hpBar[HPMAX];
	int curMaxHPBar;
	int currentIdx;
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

