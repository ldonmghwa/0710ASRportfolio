#pragma once

class Character
{
protected:
	vector<class Character*> target;
	vector<class Tile*> targetWay;
	ObRect*				col;
	ObImage*			charImg[(int)CRState::SIZE];
	ObTileMap*			tileMap;

	string				charName;
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
	wstring				file_name;
	bool				isInvincible;
	int					healPoint;
public:
	Character(string _name);
	~Character();

	ObRect* GetCol() { return col; }

	virtual void Init();
	virtual void Control();
	virtual void Update();
	virtual void Render();

	virtual void GoBack();
	virtual void Attack();
	virtual void LookTarget(Vector2 target);

	virtual void TakeDamage(int _damagePoint);
	void SetSpawnPos(Vector2 spawn){
		col->SetWorldPosX(spawn.x);
		col->SetWorldPosY(spawn.y);
	}
	void SetTarget(class Character* _target) { target.push_back(_target); }
	void SetTileMap(ObTileMap* _tileMap) { tileMap = _tileMap; }
	int GetIndex() { return index; }
	Vector2 GetFoot();
};

