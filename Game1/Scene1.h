#pragma once
class Scene1 : public Scene
{
private:

	class Mutal* mutal;
	class ObIso* map;
	float fadeout =0.0f;

	
	thread* t1;

public:
	class Player* pl;
	Scene1();
	~Scene1();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

