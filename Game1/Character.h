#pragma once

class Character
{
protected:
	ObRect*				col;
	ObImage*			idle;
	ObImage*			walk;
	ObImage*			death;
	Vector2				lastPos;
	enum class CRState 	state;
	int					dirFrame[8];
	float				speed;
public:
	Character();
	~Character();

	virtual void Init(Vector2 spawn);
	virtual void Control();
	virtual void Update();
	virtual void Render();

	void GoBack();
	virtual void Attack();
	virtual void LookTarget(Vector2 target);
};

