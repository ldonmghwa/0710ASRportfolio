#pragma once

class BulletBoss : public ASRBullet
{
private:
	float				 bulletLifeTime;
	float				 backUpBulletLifeTime;
	enum class BossScene type;
public:
	bool				 isTimeOut;
public:
	BulletBoss(wstring _wstr,
		GameObject* _shooter,
		float _power,
		wstring _deathImg,
		float _resizeScale,
		BossScene _type);
	~BulletBoss();

	void Update();
	void Render();
	void Fire();
	void SetBulletLifeTime(float _lifeTime) { bulletLifeTime = _lifeTime; }
};

