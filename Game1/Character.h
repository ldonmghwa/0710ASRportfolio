#pragma once

class Character
{
protected:
	vector<class Character*> target;
	vector<class Tile*> targetWay;
	ObRect*				col;
	ObImage*			charImg[(int)CRState::SIZE];

	string				charName;
	Vector2				lastPos;
	Vector2				controlDir;
	Vector2				dir2;

	enum class CRState 	state;

	int					index;
	int					dirFrame[8];
	int					money;
	int					moneyCount;

	float				speed;
	float				backUpSpeed;
	float				resizeValue;
public:
	ObTileMap*			tileMap;
	wstring				file_name;
	bool				isDeath;
	bool				isInvincible;
	bool				isGlitStart;
	bool				isGlit;
	int					healPoint;
	int					maxHealPoint;
	float				glitTime;
	float				backUpGlitTime;
	float				glitingTime;
	float				backUpGlitingTime;
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
	virtual void Glit();
	virtual void LookTarget(Vector2 target);
	
	virtual void TakeDamage(int _damagePoint);
	void IncreaseMoney(int _money) { money += _money; }
	void SetSpawnPos(Vector2 spawn){
		col->SetWorldPosX(spawn.x);
		col->SetWorldPosY(spawn.y);
	}
	void SetTarget(class Character* _target) { target.push_back(_target); }
	int GetIndex() { return index; }
	Vector2 GetFoot();
};

