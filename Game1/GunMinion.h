#pragma once
class GunMinion : public ASRGun
{
public:
	GunMinion(wstring _wstr, 
		Character* _player,
		vector<Character*> _target,
		GunType _type);
	~GunMinion();

	void Update() override;
	void Render() override;

	void FireBullet() override;

};

