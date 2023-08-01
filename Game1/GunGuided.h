#pragma once
class GunGuided : public ASRGun
{
private:
	ObLine* crossLineX;
	ObLine* crossLineY;
	Vector2 destPos;
public:
	GunGuided(wstring _wstr,
		Character* _player,
		vector<Character*> _target,
		GunType _type);
	~GunGuided();

	void Update() override;
	void Render() override;

	void FireBullet(Vector2 _destPos);
};

