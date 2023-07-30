#pragma once
class GunMinion : public ASRGun
{
public:
	GunMinion(wstring _wstr, ObRect* _player,
		vector<GameObject*> _target, GunType _type);
	~GunMinion();

	void Update() override;
	void Render() override;

	void FireBullet() override;

};

