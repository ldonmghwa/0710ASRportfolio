#pragma once

class ASRBullet : public Item
{
protected:
	Vector2		fireDir;
	ObImage*	deathImg;

	bool		isFire;

	int			damagePoint;
	float		pressPower;
	float		backUpPressPower;
	float		distance;
	float		resizeScale;
	float		bulletLifeTime;
	float		backUpBulletLifeTime;
public:
	bool		isHitting;
	bool		isTimeOut;
public:
	Vector2		sourcePos;
public:
	ASRBullet(wstring _wstr, GameObject* _shooter, float _power, wstring _deathImg);
	~ASRBullet();

	void Fire(GameObject* shooter, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update();
	void Render();
	void Fire();
	void Render(Camera* uicam);
	void Release() { isFire = false; }
	void SetBulletLifeTime(float _lifeTime) {
		bulletLifeTime = _lifeTime; 
		backUpBulletLifeTime = _lifeTime;
	}
	bool GetIsFire() { return isFire; }
	float GetBulletLifeTime() {
		return backUpBulletLifeTime;
	}
	bool GetDeathImgAniStop() { return deathImg->isAniStop(); }
	bool IsBulletReach();
	void IsBulletReach(ObTileMap* _tileMap);
	void IsBulletReach(vector<class Character*> target);	
};

