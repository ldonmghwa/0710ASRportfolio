#include "common.h"

GunBoss::GunBoss(wstring _wstr, 
	Character* _player, 
	vector<Character*> _target, 
	GunType _type) : ASRGun(_wstr, _player, _target, _type)
{
	timeOutCount = 0;
	isClbarAvailable = false;
	bulletNum = 100000;
	curBulletNum = bulletNum;
	bulletPower = 500.0f;
	guidedBulletPower = 100.0f;
	mazeBulletPower = 150.0f;
	reloadTime = 5.0f;
	backUpReloadTime = reloadTime;
	reloadPerSec = (reloadTime - 0.1f) / bulletNum;
	backUpReloadPerSec = reloadPerSec;
	incrementValue = 0.03f;
	rotateCount = 10.0f;
	backUpRotateCount = rotateCount;
	this->isVisible = true;
	col->SetLocalPosX(0.0f);
	col->SetLocalPosY(_player->GetCol()->scale.y * 0.2f);
	col->Update();

    mazeBulletPos.push_back("111111111111111100001111111111");
    mazeBulletPos.push_back("111111111111111100001111111111");
    mazeBulletPos.push_back("111111111111111100001111111111");
    mazeBulletPos.push_back("111111111111111100001111111111");
	mazeBulletPos.push_back("111111000000000000001111111111");
    mazeBulletPos.push_back("111111000000000000001111111111");
    mazeBulletPos.push_back("111111000000000000001111111111");
    mazeBulletPos.push_back("111111000000000000001111111111");
    mazeBulletPos.push_back("111111000000000000001111111111");
    mazeBulletPos.push_back("111111000011111111111111111111");
    mazeBulletPos.push_back("111111000011111111111111111111");
    mazeBulletPos.push_back("111111000011111111111111111111");
    mazeBulletPos.push_back("111111000011111111111111111111");
	mazeBulletPos.push_back("111111000000000000000001111111");
    mazeBulletPos.push_back("111111000000000000000001111111");
    mazeBulletPos.push_back("111111000000000000000001111111");
    mazeBulletPos.push_back("111111000000000000000001111111");
    mazeBulletPos.push_back("111111000000000000000001111111");
    mazeBulletPos.push_back("111111111111111111000001111111");
    mazeBulletPos.push_back("111111111111111111000001111111");
    mazeBulletPos.push_back("111111111111111111000001111111");
	mazeBulletPos.push_back("111111111111111111000001111111");
	mazeBulletPos.push_back("111111111111111111000001111111");
	mazeBulletPos.push_back("111111000000000000000001111111");
	mazeBulletPos.push_back("111111000000000000000001111111");
	mazeBulletPos.push_back("111111000000000000000001111111");
	mazeBulletPos.push_back("111111000000000000000001111111");
	mazeBulletPos.push_back("111111000000000000000001111111");
	mazeBulletPos.push_back("111111000011111111111111111111");
	mazeBulletPos.push_back("111111000011111111111111111111");
	mazeBulletPos.push_back("111111000011111111111111111111");
	mazeBulletPos.push_back("111111000011111111111111111111");


	for (int i = 0; i < (int)BossScene::SIZE; i++)
		shootScene[i] = false;
}

GunBoss::~GunBoss()
{
	for (auto it = mazeBullet.begin(); it != mazeBullet.end(); it++) delete (*it);
	TEXTURE->DeleteTexture(L"Agonizer_Bullet_Basic_Death_11x1.png");
	TEXTURE->DeleteTexture(L"Agonizer_Bullet_Guided_Death.png");
}

void GunBoss::Update()
{
	for (auto it = bulletCylinder.begin();
		it != bulletCylinder.end(); it++) {
		if ((*it)->GetDeathImgAniStop()) {
			bulletCylinder.erase(it);
			break;
		}
	}
	for (auto it = bulletCylinder.begin();
		it != bulletCylinder.end(); it++) {
		if (!(*it)->GetIsFire()) {
			bulletCylinder.erase(it);
			break;
		}
	}
	

	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		(*it)->IsBulletReach(target);
		(*it)->Update();
	}
	for (auto it = bulletCylinder.begin(); it != bulletCylinder.end(); it++) {
		if ((*it)->IsBulletReach()) {
			(*it)->Update();
		}
	}
	if(shootScene[(int)BossScene::MAZE]){
		if (mazeBullet.size() > 0) {
			for (int i = 0; i < mazeBulletPos.size(); i++) {
				for (int j = 0; j < mazeBulletPos.back().size(); j++) {
					if (mazeBulletPos[i][j] == '1') {
						mazeBullet[i * mazeBulletPos.back().size() + j]->IsBulletReach(target);
						mazeBullet[i * mazeBulletPos.back().size() + j]->Update();
					}
				}
			}
		}
	}
	else if (shootScene[(int)BossScene::ROTATE]) {
		if (rotateBullet.size() > 0) {
			for (int i = 0; i < rotateBullet.size(); i++) {
				rotateBullet[i]->IsBulletReach(target);
				rotateBullet[i]->Update(incrementValue);
			}
		}
	}
	else {
		if (mazeBullet.size() > 0) {
			for (auto it = mazeBullet.begin(); it != mazeBullet.end(); it++) delete (*it);
			mazeBullet.clear();
			mazeBullet.shrink_to_fit();
		}
		if (rotateBullet.size() > 0) {
			for (auto it = rotateBullet.begin(); it != rotateBullet.end(); it++) delete (*it);
			rotateBullet.clear();
			rotateBullet.shrink_to_fit();
		}
	}
	if (isVisible) {
		Item::Update();
		img->Update();
	}
}

void GunBoss::Render()
{
	ASRGun::Render();
	if (mazeBullet.size() > 0) {
		for (auto it = mazeBullet.begin(); it != mazeBullet.end(); it++)(*it)->Render();
	}
	if (rotateBullet.size() > 0) {
		for (auto it = rotateBullet.begin(); it != rotateBullet.end(); it++) (*it)->Render();
	}
}

void GunBoss::FireBullet(float _lifeTime, float _bulletPower)
{
	if (isCylinderEmpty) return;
	bulletPower = _bulletPower;
	bulletCylinder.push_back(
		new BulletBoss(L"Agonizer_Bullet_Basic.png",
			this->col,
			bulletPower,
			L"Agonizer_Bullet_Basic_Death_11x1.png",
			1.5f,
			BossScene::BASIC,
			0
		)
	);
	bulletCylinder.back()->SetBulletLifeTime(_lifeTime);
	bulletCylinder.back()->Fire();
	ASRGun::FireBullet();

}

void GunBoss::RotateBullet(float _lifeTime, float _bulletPower)
{
	if (isCylinderEmpty) return;
	bulletPower = _bulletPower;
	rotateBullet.push_back(
		new BulletBoss(L"Agonizer_Bullet_Basic.png",
			this->col,
			bulletPower,
			L"Agonizer_Bullet_Basic_Death_11x1.png",
			1.5f,
			BossScene::BASIC,
			1.0f
		)
	);
	rotateBullet.back()->GetCol()->SetParentRT(*(this->col));
	rotateCount = 10.0f;
	rotateBullet.back()->GetCol()->SetLocalPosX(rotateCount);
	cout << rotateBullet.back()->GetCol()->GetLocalPos().x << ", "
		<< rotateBullet.back()->GetCol()->GetLocalPos().y << endl;
	rotateBullet.back()->GetCol()->Update();
	rotateBullet.back()->SetBulletLifeTime(_lifeTime);
	rotateBullet.back()->Fire();
	ASRGun::FireBullet();

}

void GunBoss::MazeBullet()
{
	if (isCylinderEmpty) return;
	int size;
	for (int i = 0; i < mazeBulletPos.size(); i++) {
		for (int j = 0; j < mazeBulletPos.back().size(); j++) {
			mazeBullet.push_back(
				new BulletBoss(L"Agonizer_Bullet_Basic.png",
					this->col,
					mazeBulletPower,
					L"Agonizer_Bullet_Basic_Death_11x1.png",
					3.0f,
					BossScene::MAZE,
					0
				)
			);
			mazeBullet.back()->SetBulletLifeTime(0.416f * mazeBulletPos.size());
			size = mazeBulletPos.back().size() / 2;
			mazeBullet.back()->GetCol()->SetWorldPos(
				Vector2(
					col->GetWorldPos().x - size * mazeBullet.back()->GetCol()->scale.x + j * mazeBullet.back()->GetCol()->scale.x,
					col->GetWorldPos().y + i * mazeBullet.back()->GetCol()->scale.y
				)
			);
			if (mazeBulletPos[i][j] == '0') {
				mazeBullet.back()->isVisible = false;
			}
			else {
				mazeBullet.back()->isVisible = true;
			}
			mazeBullet.back()->Fire();
		}
	}
}

void GunBoss::GuideBullet(Character* _target)
{
	if (isCylinderEmpty) return;
	bulletCylinder.push_back(
		new BulletBossGuided(L"Agonizer_Bullet_Guided.png",
			_target,
			this->col,
			guidedBulletPower,
			L"Agonizer_Bullet_Guided_Death.png"
		)
	);
	bulletCylinder.back()->SetBulletLifeTime(guidedShootingInterval * 3 + 5.0f);
	ASRGun::FireBullet();
}
