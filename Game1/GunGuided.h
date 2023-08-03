#pragma once
class GunGuided : public ASRGun
{
private:
	ObRect* crossLineX;
	ObRect* crossLineY;
	Vector2 destPos;
public:
	float	aimingTime;
	float	backUpAimingTime;
public:
	GunGuided(wstring _wstr,
		Character* _player,
		vector<Character*> _target,
		GunType _type);
	~GunGuided();

	void Update() override;
	void Render() override;

	void FireBullet();
	void FireBullet(Character* _destPos);
};

