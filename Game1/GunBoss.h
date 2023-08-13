#pragma once

class GunBoss : public ASRGun
{
private:
	vector<string> mazeBulletPos;
	vector<BulletBoss*> mazeBullet;
	vector<BulletBoss*> rotateBullet;
	int timeOutCount;
	float guidedBulletPower;
	float mazeBulletPower;
	float rotateYPosIncrementValue;
	float rotateXPos;
	float backUpRotateCount;
	enum class BossScene bstype;
public:
	bool shootScene[(int)BossScene::SIZE];
	float guidedShootingInterval;
	int shootSceneIdx;
	string rotateSoundKey;
	string mazeSoundKey;
	string guideSoundKey;
	string rotateGuideSoundKey;
public:
	GunBoss(wstring _wstr,
		Character* _player,
		vector<Character*> _target,
		GunType _type);
	~GunBoss();

	void Update() override;
	void Render() override;

	void FireBullet(float _lifeTime, float _bulletPower);
	void RotateBullet(float _lifeTime, float _bulletPower);
	void MazeBullet();
	void GuideBullet();
	void RotateGuideBullet();
};

