#pragma once

class Character
{
protected:
	vector<GameObject*> target;
	ObRect*				col;
	ObImage*			charImg[(int)CRState::SIZE];

	Vector2				lastPos;
	Vector2				controlDir;
	Vector2				dir2;

	enum class CRState 	state;
	int					index;
	int					dirFrame[8]; 
	float				speed;
	float				backUpSpeed;
	float				resizeValue;
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

	void SetTarget(GameObject* _target) { target.push_back(_target); }

	Vector2 GetFoot();
};

