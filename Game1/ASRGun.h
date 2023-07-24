#pragma once
class ASRGun : public ObImage
{
private:
	enum class GunType type;
	vector<class ASRBullet*> bulletCyliner;
	int bulletNum;
	float bulletPower;
public:
	ASRGun(wstring _wstr, class Player* _player);
	~ASRGun();

	void Update() override;
	void Render() override;

	void FireBullet();
};

