#pragma once
class ASRGun : public Item
{
private:
	enum class GunType gunType;
	static vector<class ASRBullet*> bulletCyliner;
	int bulletNum;
	float bulletPower;
public:
	ASRGun(wstring _wstr, ObRect* _player, 
		GunType _type);
	~ASRGun();

	void Update() override;
	void Render() override;

	void FireBullet();
	static vector<class ASRBullet*> GetVector() {
		return bulletCyliner;
	}
};

