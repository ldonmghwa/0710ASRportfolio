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
	bulletPower = 200.0f;
	mazeBulletPower = 150.0f;
	reloadTime = 5.0f;
	backUpReloadTime = reloadTime;
	reloadPerSec = (reloadTime - 0.1f) / bulletNum;
	backUpReloadPerSec = reloadPerSec;

	this->isVisible = true;
	col->SetLocalPosX(0.0f);
	col->SetLocalPosY(_player->GetCol()->scale.y * 0.2f);
	col->Update();

    mazeBulletPos.push_back("111111111110000111111");
    mazeBulletPos.push_back("111111111110000111111");
    mazeBulletPos.push_back("111111111110000111111");
    mazeBulletPos.push_back("111111111110000111111");
    mazeBulletPos.push_back("100000000000000111111");
    mazeBulletPos.push_back("100000000000000111111");
    mazeBulletPos.push_back("100000000000000111111");
    mazeBulletPos.push_back("100000000000000111111");
    mazeBulletPos.push_back("100001111111111111111");
    mazeBulletPos.push_back("100001111111111111111");
    mazeBulletPos.push_back("100001111111111111111");
    mazeBulletPos.push_back("100001111111111111111");
    mazeBulletPos.push_back("100000000000000000111");
    mazeBulletPos.push_back("100000000000000000111");
    mazeBulletPos.push_back("100000000000000000111");
    mazeBulletPos.push_back("100000000000000000111");
    mazeBulletPos.push_back("111111111111100000111");
    mazeBulletPos.push_back("111111111111100000111");
    mazeBulletPos.push_back("111111111111100000111");
	mazeBulletPos.push_back("111111111111100000111");
	mazeBulletPos.push_back("111111111111100000111");
	mazeBulletPos.push_back("100000000000000000111");
	mazeBulletPos.push_back("100000000000000000111");
	mazeBulletPos.push_back("100000000000000000111");
	mazeBulletPos.push_back("100000000000000000111");
	mazeBulletPos.push_back("100001111111111111111");
	mazeBulletPos.push_back("100001111111111111111");
	mazeBulletPos.push_back("100001111111111111111");
	mazeBulletPos.push_back("100001111111111111111");


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
		if (!(*it)->GetIsFire()) {
			bulletCylinder.erase(it);
			break;
		}
	}
	for (auto it = bulletCylinder.begin();
		it != bulletCylinder.end(); it++) {
		if ((*it)->GetDeathImgAniStop()) {
			bulletCylinder.erase(it);
			break;
		}
	}
	/*if (mazeBullet.size() > 0) {
		for (auto it = mazeBullet.begin(); it != mazeBullet.end(); it++) {
			if ((*it)->isTimeOut) {
				timeOutCount++;
				mazeBullet.erase(it);
				break;
			}
		}
	}
	if (mazeBullet.size() > 0) {
		if (timeOutCount == mazeBullet.size()) {
			mazeBullet.clear();
			mazeBullet.shrink_to_fit();
		}
	}*/
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
					
						mazeBullet[i * mazeBulletPos.back().size() + j]->IsBulletReach(target);
						mazeBullet[i * mazeBulletPos.back().size() + j]->Update();
					
				}
			}
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
}

void GunBoss::FireBullet()
{
	if (isCylinderEmpty) return;
	bulletCylinder.push_back(
		new BulletBoss(L"Agonizer_Bullet_Basic.png",
			this->col,
			bulletPower,
			L"Agonizer_Bullet_Basic_Death_11x1.png",
			1.5f,
			BossScene::BASIC
		)
	);
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
					BossScene::MAZE
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
			100,
			L"Agonizer_Bullet_Guided_Death.png"
		)
	);
	ASRGun::FireBullet();
}
