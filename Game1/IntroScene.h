#pragma once
class IntroScene : public Scene
{
private:
	ObImage* titleImage;
	ObRect* playButton;
	ObRect* endButton;
	float playButtonScale;
	float endButtonScale;
	bool isPlayButtonOn;
	bool isEndButtonOn;

public:
	IntroScene();
	~IntroScene();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

