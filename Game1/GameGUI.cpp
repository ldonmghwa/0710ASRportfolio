#include "common.h"

GameGUI::GameGUI()
{
	for (int i = 0; i < HPMAX; i++) hpBar[i] = new HPBar();
	for (int i = 0; i < BBMAX; i++) bbBar[i] = new BBBar();
	hpBar[3]->heartBar[0]->isVisible = false;
	hpBar[4]->heartBar[0]->isVisible = false;
	cylinderBarTP[0] = new ObImage(L"CylinderUp.png");
	cylinderBarTP[1] = new ObImage(L"CylinderDown.png");
	for (int i = 0; i < 2; i++) {
		cylinderBarTP[i]->scale.x = cylinderBarTP[i]->imageSize.x;
		cylinderBarTP[i]->scale.y = cylinderBarTP[i]->imageSize.y;
	}
	
	boxKeyImg = new ObImage(L"TreasureBoxKey.png");
	boxKeyImg->scale.x = boxKeyImg->imageSize.x * 4.0f;
	boxKeyImg->scale.y = boxKeyImg->imageSize.y * 4.0f;

	moneyImg = new ObImage(L"Money.png");
	moneyImg->scale.x = moneyImg->imageSize.x * 4.0f;
	moneyImg->scale.y = moneyImg->imageSize.y * 4.0f;

	uiCam = new Camera();

}

GameGUI::~GameGUI()
{
	for (int i = 0; i < HPMAX; i++) delete hpBar[i];
	for (int i = 0; i < BBMAX; i++) delete bbBar[i];
	for (int i = 0; i < 2; i++)delete cylinderBarTP[i];
	for (auto it = clBar.begin(); it != clBar.end(); it++) delete (*it);
	delete boxKeyImg;
	delete moneyImg;
	delete uiCam;
	TEXTURE->DeleteTexture(L"HeartBarFull.png");
	TEXTURE->DeleteTexture(L"HeartBarHalf.png");
	TEXTURE->DeleteTexture(L"HeartBarZero.png");

	TEXTURE->DeleteTexture(L"BlankBulletFull.png");
	TEXTURE->DeleteTexture(L"BlankBulletZero.png");

	TEXTURE->DeleteTexture(L"BasicBulletFull.png");
	TEXTURE->DeleteTexture(L"BasicBulletZero.png");

	TEXTURE->DeleteTexture(L"CylinderUp.png");
	TEXTURE->DeleteTexture(L"CylinderDown.png");

	TEXTURE->DeleteTexture(L"TreasureBoxKey.png");
	TEXTURE->DeleteTexture(L"Money.png");
}

void GameGUI::Init(int _bulletNum)
{
	basicBulletNum = _bulletNum;
	beforeBasicBulletNum = basicBulletNum;
	clBar.clear();
	clBar.reserve(basicBulletNum);
	for (int i = 0; i < basicBulletNum; i++) {
		clBar.push_back(new CLBar(GunType::BASIC));
	}
	curMaxHPBar = 3;
	curHPIdx = curMaxHPBar - 1;
	curMaxBBBar = 2;
	curBBIdx = curMaxBBBar - 1;
	curCLIdx = basicBulletNum - 1;
	boxKeyNum = 0;
	moneyNum = 0;
}

void GameGUI::Update()
{
	uiCam->Set();
	for (int i = 0; i < curMaxHPBar; i++) {
		hpBar[i]->heartBar[0]->SetWorldPosX(uiCam->position.x - 760.0f + i * 70.0f);
		hpBar[i]->heartBar[0]->SetWorldPosY(uiCam->position.y + 450.0f);
		hpBar[i]->heartBar[1]->SetWorldPosX(uiCam->position.x - 760.0f + i * 70.0f);
		hpBar[i]->heartBar[1]->SetWorldPosY(uiCam->position.y + 450.0f);
		hpBar[i]->heartBar[2]->SetWorldPosX(uiCam->position.x - 760.0f + i * 70.0f);
		hpBar[i]->heartBar[2]->SetWorldPosY(uiCam->position.y + 450.0f);
		hpBar[i]->heartBar[0]->Update();
		hpBar[i]->heartBar[1]->Update();
		hpBar[i]->heartBar[2]->Update();
	}
	for (int i = 0; i < curMaxBBBar; i++) {
		bbBar[i]->blankBulletBar[0]->SetWorldPosX(uiCam->position.x - 760.0f + i * 70.0f);
		bbBar[i]->blankBulletBar[0]->SetWorldPosY(uiCam->position.y + 390.0f);
		bbBar[i]->blankBulletBar[1]->SetWorldPosX(uiCam->position.x - 760.0f + i * 70.0f);
		bbBar[i]->blankBulletBar[1]->SetWorldPosY(uiCam->position.y + 390.0f);
		bbBar[i]->blankBulletBar[0]->Update();
		bbBar[i]->blankBulletBar[1]->Update();
	}
	for (int i = 0; i < clBar.size(); i++) {
		clBar[i]->cylinderBar[0]->SetWorldPosX(uiCam->position.x + 785.0f);
		clBar[i]->cylinderBar[0]->SetWorldPosY(uiCam->position.y - 475.0f + i * 15.0f);
		clBar[i]->cylinderBar[1]->SetWorldPosX(uiCam->position.x + 785.0f);
		clBar[i]->cylinderBar[1]->SetWorldPosY(uiCam->position.y - 475.0f + i * 15.0f);
		clBar[i]->cylinderBar[0]->Update();
		clBar[i]->cylinderBar[1]->Update();
	}
	cylinderBarTP[0]->SetWorldPosX(uiCam->position.x + 785.0f);
	cylinderBarTP[0]->SetWorldPosY(uiCam->position.y - 475.0f + clBar.size() * 15.0f);
	cylinderBarTP[1]->SetWorldPosX(uiCam->position.x + 785.0f);
	cylinderBarTP[1]->SetWorldPosY(uiCam->position.y - 490.0f);
	cylinderBarTP[0]->Update();
	cylinderBarTP[1]->Update();

	boxKeyImg->SetWorldPosX(uiCam->position.x - 760.0f);
	boxKeyImg->SetWorldPosY(uiCam->position.y + 330.0f);
	moneyImg->SetWorldPosX(uiCam->position.x - 590.0f);
	moneyImg->SetWorldPosY(uiCam->position.y + 330.0f);
	boxKeyImg->Update();
	moneyImg->Update();


	//Utility::Saturate(curHPIdx, 0, curMaxHPBar - 1);
	if (INPUT->KeyDown('Z')) {
		if (hpBar[curHPIdx]->hpBarState == HPBarState::ZERO) curHPIdx--;
		if (curHPIdx < 0) curHPIdx = 0;
		hpBar[curHPIdx]->hpBarState -= 1;
		if (hpBar[curHPIdx]->hpBarState < 0) hpBar[curHPIdx]->hpBarState = 0;
	}
	if (INPUT->KeyDown('X')) {
		if (bbBar[curBBIdx]->bBarState == 0) curBBIdx--;
		if (curBBIdx < 0) curBBIdx = 0;
		bbBar[curBBIdx]->bBarState -= 1;
		if (bbBar[curBBIdx]->bBarState < 0) bbBar[curBBIdx]->bBarState = 0;
		cout << "bbBar state: " << bbBar[curBBIdx]->bBarState << endl;
	}
	/*if (INPUT->KeyDown('C')) {
		if (clBar[curCLIdx]->cBarState == 0) curCLIdx--;
		if (curCLIdx < 0) curCLIdx = 0;
		clBar[curCLIdx]->cBarState -= 1;
		if (clBar[curCLIdx]->cBarState < 0)clBar[curCLIdx]->cBarState = 0;
	}*/


}

void GameGUI::Render()
{
	for (int i = 0; i < curMaxHPBar; i++) {
		if (hpBar[i]->hpBarState == HPBarState::FULL) hpBar[i]->heartBar[0]->Render(uiCam);
		else if (hpBar[i]->hpBarState == HPBarState::HALF) hpBar[i]->heartBar[1]->Render(uiCam);
		else if (hpBar[i]->hpBarState == HPBarState::ZERO) hpBar[i]->heartBar[2]->Render(uiCam);
	}

	for (int i = 0; i < curMaxBBBar; i++) {
		if (bbBar[i]->bBarState == 1) bbBar[i]->blankBulletBar[0]->Render(uiCam);
		else if (bbBar[i]->bBarState == 0) bbBar[i]->blankBulletBar[1]->Render(uiCam);
	}

	for (auto it = clBar.begin(); it != clBar.end(); it++) {
		if ((*it)->cBarState == 1) (*it)->cylinderBar[0]->Render(uiCam);
		else if ((*it)->cBarState == 0) (*it)->cylinderBar[1]->Render(uiCam);
	}
	cylinderBarTP[0]->Render(uiCam);
	cylinderBarTP[1]->Render(uiCam);
	boxKeyImg->Render(uiCam);
	moneyImg->Render(uiCam);

	boxKeyRc;
	boxKeyRc.left = Utility::WorldToScreen(boxKeyImg->GetWorldPos(), uiCam).x + 35.0f;
	boxKeyRc.top = Utility::WorldToScreen(boxKeyImg->GetWorldPos(), uiCam).y - 25.0f;
	boxKeyRc.right = boxKeyRc.left + 100.0f;
	boxKeyRc.bottom = boxKeyRc.top + 50.0f;

	DWRITE->RenderText(L"¡¿" + to_wstring(boxKeyNum), boxKeyRc, 50.0f, L"µÕ±Ù¸ð²Ã", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_EXPANDED);

	RECT moneyNumRc;
	moneyNumRc.left = Utility::WorldToScreen(moneyImg->GetWorldPos(), uiCam).x + 30.0f;
	moneyNumRc.top = Utility::WorldToScreen(moneyImg->GetWorldPos(), uiCam).y - 25.0f;
	moneyNumRc.right = moneyNumRc.left + 100.0f;
	moneyNumRc.bottom = moneyNumRc.top + 50.0f;
	DWRITE->RenderText(L"¡¿" + to_wstring(moneyNum), moneyNumRc, 50.0f, L"µÕ±Ù¸ð²Ã", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_EXPANDED);

}

void GameGUI::ConsumeBullet(bool isCylinderEmpty)
{
	if (isCylinderEmpty) return;
	if (clBar[curCLIdx]->cBarState == 0) curCLIdx--;
	if (curCLIdx < 0) curCLIdx = 0;
	clBar[curCLIdx]->cBarState -= 1;
	if (clBar[curCLIdx]->cBarState < 0)clBar[curCLIdx]->cBarState = 0;
}

void GameGUI::ReLoadingBulletBar(float& reloadPerSec, float reloadTime)
{
	reloadPerSec -= DELTA;
	if (reloadPerSec < 0.0f) {
		clBar[curCLIdx]->cBarState = 1;
		curCLIdx++;
		reloadPerSec = reloadTime;
		if (curCLIdx == clBar.size()) curCLIdx--;
	}
}

void GameGUI::ReduceHPBar()
{
	
}

void GameGUI::ReduceBBBar()
{
}

void GameGUI::IncreaseMoneyBar()
{
}
