#pragma once
class BulletMinion : public ASRBullet
{
public:
	BulletMinion(wstring _wstr, 
		GameObject* _shooter, 
		float _power,
		wstring _deathImg);
	~BulletMinion();

	void Update();
	void Render() override;
};

