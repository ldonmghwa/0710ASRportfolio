#pragma once
class ASRGun : public Item
{
protected:
	vector<GameObject*>		 target;
	enum class GunType		 gunType;
	wstring					 gunFileName;
	vector<class ASRBullet*> bulletCylinder;
							 
	bool					 isCylinderEmpty;
	int						 bulletNum;
	int						 curBulletNum; 
	float					 resizeValue;
	float					 bulletPower;
	float					 reloadTime;
	float					 backUpReloadTime;
public:
	bool isReloading;

public:
	ASRGun(wstring _wstr, ObRect* _player, 
		vector<GameObject*> _target, GunType _type);
	~ASRGun();

	virtual void Update() override;
	virtual void Render() override;

	virtual void FireBullet();
	void GunReLoading();

	vector<class ASRBullet*> GetBulletVector() { return bulletCylinder; }
	bool GetIsCylinderEmpty() { return isCylinderEmpty; }
	int GetBulletNum() { return bulletNum; }
	float GetReloadTime() { return reloadTime; }
};

