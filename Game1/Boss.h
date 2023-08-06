#pragma once


class Boss : public Character
{
private:
	enum class MTType monsterType;
	class GunBoss* gun;


	float attackRange;
	float detectionRange;
	float shootingInterval;
	float backUpShootingInterval;

	float shootSceneChangeTime;
	float backUpShootSceneChangeTime;
	float mazeBulletLifeTime;
	float backUpMazeBulletLifeTime;

	Vector2 dest;
	Vector2 source;
public:
	Vector2 spawnPos; 
	bool isSetSpawning;
public:
	Boss(string _name);
	~Boss();

	void Init();
	void Update();
	void Render();

	void LookTarget(Vector2 target);
};

