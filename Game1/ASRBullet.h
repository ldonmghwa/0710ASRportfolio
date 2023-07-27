#pragma once

class ASRBullet : public Item
{
protected:
	Vector2		fireDir;

	float		pressPower;
	float		distance;
	bool		isFire;
public:
	Vector2		sourcePos;
	ASRBullet(wstring _wstr);
	~ASRBullet();

	void Fire(GameObject* shooter, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update();
	void Render();
	bool GetIsFire() { return isFire; }
	bool IsBulletReach();
	void Release() { isFire = false; }
};

