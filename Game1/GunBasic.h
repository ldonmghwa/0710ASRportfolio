#pragma once
class GunBasic : public ASRGun
{
public:
	GunBasic(wstring _wstr, Character* _player,
		vector<Character*> _target, GunType _type);
	~GunBasic();

	void Update() override;
	void Render() override;

	void FireBullet() override;
};

