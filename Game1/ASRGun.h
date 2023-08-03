#pragma once
class ASRGun : public Item
{
protected:
	vector<class Character*> target;
	vector<class ASRBullet*> bulletCylinder;
	vector<class CLBar*>	 clbarList;
	class Character*		 parentChar;
	enum class GunType		 gunType;
	wstring					 gunFileName;
	ObImage*				 cylinderBarTP[2];

	bool					 isCylinderEmpty;
	bool					 isClbarAvailable;
	int						 bulletNum;
	int						 curBulletNum;
	int						 curCLIdx;
	float					 resizeScale;
	float					 bulletPower;
	float					 reloadTime;
	float					 backUpReloadTime;
	float					 reloadPerSec;
	float					 backUpReloadPerSec;
public:
	bool					 isReloading;
	bool					 isAiming;
public:
	ASRGun(wstring _wstr,
		Character* _player,
		vector<Character*> _target,
		GunType _type);
	~ASRGun();

	virtual void Update() override;
	virtual void Render() override;

	virtual void FireBullet();
	void GunReLoading();
	void GunReLoading(bool& isGunReloading);
	void ReduceClbarImg();
	void ReloadingClbarImg();

	vector<class ASRBullet*> GetBulletVector() { return bulletCylinder; }
	GunType GetGunType() { return gunType; }
	bool GetIsCylinderEmpty() { return isCylinderEmpty; }
	int GetBulletNum() { return bulletNum; }
	float GetReloadTime() { return reloadTime; }
};

