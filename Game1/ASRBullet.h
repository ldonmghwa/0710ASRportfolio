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
	ASRBullet(wstring _wstr, GameObject* _shooter, float _power );
	~ASRBullet();

	void Fire(GameObject* shooter, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update();
	void Render();
	void Release() { isFire = false; }
	bool GetIsFire() { return isFire; }
	bool IsBulletReach();
	bool IsBulletReach(vector<GameObject*> target);
};

