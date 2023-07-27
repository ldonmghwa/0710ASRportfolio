#pragma once
class GunBasic : public ASRGun
{
public:
	GunBasic(wstring _wstr, ObRect* _player,
		GunType _type);
	~GunBasic();

	void Update() override;
	void Render() override;

	void FireBullet() override;
};

