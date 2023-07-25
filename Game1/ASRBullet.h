#pragma once

class ASRBullet : public ObImage
{
protected:
	Vector2		fireDir;
	Vector2		sourcePos;
	wstring		bulletName;
	// ฝ๎ดย ศ๛
	float		pressPower;
	float		distance;
	bool		isFire;
public:
	ASRBullet(wstring _wstr, class ASRGun* _gun);
	~ASRBullet();

	void Fire(GameObject* shooter, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update();
	void Render();
	bool GetIsFire() { return isFire; }
	void Release() { isFire = false; }
};

