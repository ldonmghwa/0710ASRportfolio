#pragma once

class BulletBoss : public ASRBullet
{
private:
	float				 backUpBulletLifeTime;
	float				 dis;
	enum class BossScene type;
public:
	bool				 isTimeOut;
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

