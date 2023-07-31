#pragma once

class ASRBullet : public Item
{
protected:
	Vector2		fireDir;
	ObImage*	bulletDeath;

	bool		isFire;
	bool		isBulletDeath;
	float		pressPower;
	float		distance;
	float		resizeScale;
public:
	Vector2		sourcePos;
	ASRBullet(wstring _wstr, GameObject* _shooter, float _power );
	~ASRBullet();

	void Fire(GameObject* shooter, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update();
	void Render();
	void Release() { isFire = false; }
	void SetBulletDeathImg(wstring _fileName);
	bool GetIsFire() { return isFire; }
	bool IsBulletReach();
	void IsBulletReach(vector<class Character*> target);
};

