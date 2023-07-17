#pragma once

class Main : public Scene
{
private:
	class IntroScene* introSc;
	class MainGameScene* mainGSc;
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
