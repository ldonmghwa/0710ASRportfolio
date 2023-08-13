#pragma once
class BulletBossRotateGuide : public BulletGuided
{
private:
	bool isRotate[3];
	float rotateTime;
	float backUpRotateTime;
	float stopTime;
	float dis;
	Vector2 targetLastPos;
	Vector2 sourcPos;
public:
	BulletBossRotateGuide(wstring _wstr,
		Character* _target,
		GameObject* _shooter,
		float _power,
		wstring _deathImg);
	~BulletBossRotateGuide();

	void Update();
	void Render() override;
};

