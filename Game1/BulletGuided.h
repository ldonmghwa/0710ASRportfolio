#pragma once
class BulletGuided : public ASRBullet
{
private:
	Vector2 destPos;
public:
	BulletGuided(wstring _wstr, 
		Vector2 _destPos, 
		GameObject* _shooter, 
		float _power,
		wstring _deathImg);
	~BulletGuided();

	void Update();
	void Render() override;
};

