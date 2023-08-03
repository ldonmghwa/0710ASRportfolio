#pragma once
class BulletGuided : public ASRBullet
{
private:
	class Character* target;
public:
	BulletGuided(wstring _wstr, 
		Character* _target,
		GameObject* _shooter, 
		float _power,
		wstring _deathImg);
	~BulletGuided();

	void Update();
	void Render() override;
};

