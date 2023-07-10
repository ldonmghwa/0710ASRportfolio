#pragma once
#define BONOMAX 11
#define SCOREMAX 30

class Main : public Scene
{

private:
	ObImage* bg;
	ObImage* bg2;
	class Sonic* sonic;
	class Bono* bono[BONOMAX];
	class Score* score[SCOREMAX];
	int	  socreSpawnY;

	float vol1 = 1.0f;
	float vol2 = 1.0f;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
