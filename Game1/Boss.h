#pragma once
class Boss : public Monster
{
private:
public:
	Boss();
	~Boss();

	void Init();
	void Update();
	void Render();

	void LookTarget(Vector2 target);
};

