#pragma once
class Scene2 : public Scene
{
private:

	class Mutal* mutal;
	class ObIso* map;
public:
	class Player* pl;
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

