#pragma once
class ASRGun : public Item
{
protected:
	enum class GunType gunType;
	wstring gunFileName;
	static vector<class ASRBullet*> bulletCylinder;
	int bulletNum;
	float bulletPower;
public:
	ASRGun(wstring _wstr, ObRect* _player, 
		GunType _type);
	~ASRGun();

	void Update() override;
	void Render() override;

	virtual void FireBullet();
	static vector<class ASRBullet*> GetVector() {
		return bulletCylinder;
	}
};

