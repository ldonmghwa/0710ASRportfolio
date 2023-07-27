#pragma once
class ASRGun : public Item
{
protected:
	enum class GunType gunType;
	wstring gunFileName;
	vector<class ASRBullet*> bulletCylinder;
	
	bool isReloading;
	int bulletNum;
	int beforeBulletNum;
	float bulletPower;
	float reloadTime;
	float beforeReloadTime;
public:
	ASRGun(wstring _wstr, ObRect* _player, 
		GunType _type);
	~ASRGun();

	virtual void Update() override;
	virtual void Render() override;

	virtual void FireBullet();
	vector<class ASRBullet*> GetVector() {
		return bulletCylinder;
	}
};

