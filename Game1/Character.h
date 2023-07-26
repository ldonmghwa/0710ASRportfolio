#pragma once

class Character
{
protected:
	ObRect*				col;
	ObImage*			idle;
	ObImage*			walk;
	ObImage*			death;
	Vector2				lastPos;
	Vector2				controlDir;
	Vector2				dir2;
	enum class CRState 	state;
	int					dirFrame[8];
	float				speed;
public:
	Character();
	~Character();

	ObRect* GetCol() { return col; }

	virtual void Init(Vector2 spawn);
	virtual void Control();
	virtual void Update();
	virtual void Render();

	virtual void GoBack();
	virtual void Attack();
	virtual void LookTarget(Vector2 target);

	Vector2 GetFoot();
};

