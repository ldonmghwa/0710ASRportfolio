#pragma once
class GunGuided : public ASRGun
{
private:
	Vector2 destPos;
public:
	GunGuided();
	~GunGuided();

	void Update() override;
	void Render() override;

	void FireBullet();
};

