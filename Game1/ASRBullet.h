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
public:
	bool		isHitting;
public:
	Vector2		sourcePos;
	ASRBullet(wstring _wstr, GameObject* _shooter, float _power, wstring _deathImg);
	~ASRBullet();

	void Fire(GameObject* shooter, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update();
	void Render();
	void Render(Camera* uicam);
	void Release() { isFire = false; }
	bool GetIsFire() { return isFire; }
	bool GetDeathImgAniStop() { return deathImg->isAniStop(); }
	bool IsBulletReach();
	void IsBulletReach(vector<class Character*> target);	
};

