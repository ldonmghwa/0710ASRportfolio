#pragma once
class GunGuided : public ASRGun
{
private:
	Vector2 destPos;
public:
	GunGuided(wstring _wstr, ObRect* _player,
		vector<GameObject*> _target, GunType _type);
	~GunGuided();

	void Update() override;
	void Render() override;

	void FireBullet(Vector2 _destPos);
};

