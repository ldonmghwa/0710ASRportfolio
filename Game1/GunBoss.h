#pragma once

class GunBoss : public ASRGun
{
private:
	vector<BulletBoss*> mazeBullet;
	vector<string> mazeBulletPos;
	int timeOutCount;
	float mazeBulletPower;
	enum class BossScene bstype;
public:
	bool shootScene[(int)BossScene::SIZE];
	int shootSceneIdx;
public:
	GunBoss(wstring _wstr,
		Character* _player,
		vector<Character*> _target,
		GunType _type);
	~GunBoss();

	void Update() override;
	void Render() override;

	void FireBullet() override;
	void MazeBullet();
	void GuideBullet(Character* _target);

};

