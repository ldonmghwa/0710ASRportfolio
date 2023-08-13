#pragma once

class BulletBoss : public ASRBullet
{
private:
	bool				 isRotateChange;
	float				 backUpBulletLifeTime;
	float				 dis;
	float				 incrementValue;
	enum class BossScene type;
public:
	BulletBoss(wstring _wstr,
		GameObject* _shooter,
		float _power,
		wstring _deathImg,
		float _resizeScale,
		BossScene _type,
		float _dis);
	~BulletBoss();

	void Update();
	void Update(float _dis);
	void Render();
};

