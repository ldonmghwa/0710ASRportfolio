#pragma once

class ASRBullet : public ObImage
{
private:
	Vector2		fireDir;
	wstring		bulletName;
	// ฝ๎ดย ศ๛
	float		pressPower;
	bool		isFire;
	float		lifeTime;
public:
	ASRBullet(wstring _wstr, ASRGun* _gun);
	~ASRBullet();

	void Fire(GameObject* shooter, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update() override;
	void Render() override;
	bool GetIsFire() { return isFire; }
	void Release() { isFire = false; }
};

