#pragma once
class GunBasic : public ASRGun
{
public:
	GunBasic(wstring _wstr, ObRect* _player,
		vector<GameObject*> _target, GunType _type);
	~GunBasic();

	void Update() override;
	void Render() override;

	void FireBullet() override;
};

