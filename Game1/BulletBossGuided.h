#pragma once
class BulletBossGuided : public BulletGuided
{
public:
	BulletBossGuided(wstring _wstr,
		Character* _target,
		GameObject* _shooter,
		float _power,
		wstring _deathImg);
	~BulletBossGuided();

	void Update();
	void Render() override;
};

