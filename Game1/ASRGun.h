#pragma once
class ASRGun : public Item
{
protected:
	vector<class Character*>		 target;
	vector<class ASRBullet*> bulletCylinder;
	class Character*		 parentChar;
	enum class GunType		 gunType;
	wstring					 gunFileName;
							 
	bool					 isCylinderEmpty;
	bool					 isHit;
	int						 bulletNum;
	int						 curBulletNum; 
	float					 resizeValue;
	float					 bulletPower;
	float					 reloadTime;
	float					 backUpReloadTime;
public:
	bool isReloading;

public:
	ASRGun(wstring _wstr, Character* _player,
		vector<Character*> _target, GunType _type);
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

