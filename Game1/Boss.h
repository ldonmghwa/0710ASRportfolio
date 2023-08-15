#pragma once


class Boss : public Character
{
private:
	enum class MTType monsterType;
	class GunBoss* gun;
	
	bool isRotateChange;

	float attackRange;
	float detectionRange;
	float basicShootingInterval;
	float backUpBasicShootingInterval;
	float guidedShootingInterval;
	float backUpGuidedShootingInterval;
	float rotateShootingInterval;
	float backUpRotateShootingInterval;
	float rotateGuideShootingInterval;
	float backUpRotateGuideShootingInterval;

	float shootSceneChangeTime;
	float backUpShootSceneChangeTime;
	float mazeBulletLifeTime;
	float backUpMazeBulletLifeTime;
	float incrementValue;

	Vector2 dest;
	Vector2 source;
public:
	Vector2 spawnPos;
	Vector2 targetSpawnPos;
	bool isSetSpawning;
public:
	Boss(string _name);
	~Boss();

	void Init();
	void Update();
	void Render();

	void TargetSearch();
	void LookTarget(Vector2 target);
	void SetmazeBulletLifeTime(float _time) {
		mazeBulletLifeTime = _time;
		backUpMazeBulletLifeTime = mazeBulletLifeTime;
	}
};

