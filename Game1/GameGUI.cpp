#include "common.h"

GameGUI::GameGUI()
{
	for (int i = 0; i < HPMAX; i++) hpBar[i] = new HPBar();
	for (int i = 0; i < BBMAX; i++) bbBar[i] = new BBBar();
	hpBar[3]->heartBar[0]->isVisible = false;
	hpBar[4]->heartBar[0]->isVisible = false;
	
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
	delete boxKeyImg;
	delete moneyImg;
	delete uiCam;
	TEXTURE->DeleteTexture(L"HeartBarFull.png");
	TEXTURE->DeleteTexture(L"HeartBarHalf.png");
	TEXTURE->DeleteTexture(L"HeartBarZero.png");

	TEXTURE->DeleteTexture(L"BlankBulletFull.png");
	TEXTURE->DeleteTexture(L"BlankBulletZero.png");

	TEXTURE->DeleteTexture(L"TreasureBoxKey.png");
	TEXTURE->DeleteTexture(L"Money.png");
}

void GameGUI::Init(int _bulletNum)
{
	basicBulletNum = _bulletNum;
	backUpBasicBulletNum = basicBulletNum;
	curMaxHPBar = 3;
	curHPIdx = curMaxHPBar - 1;
	curMaxBBBar = 2;
	curBBIdx = curMaxBBBar - 1;
	boxKeyNum = 3;
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

	boxKeyImg->SetWorldPosX(uiCam->position.x - 760.0f);
	boxKeyImg->SetWorldPosY(uiCam->position.y + 330.0f);
	moneyImg->SetWorldPosX(uiCam->position.x - 590.0f);
	moneyImg->SetWorldPosY(uiCam->position.y + 330.0f);
	boxKeyImg->Update();
	moneyImg->Update();


	if (INPUT->KeyDown('X')) {
		if (bbBar[curBBIdx]->bBarState == 0) curBBIdx--;
		if (curBBIdx < 0) curBBIdx = 0;
		bbBar[curBBIdx]->bBarState -= 1;
		if (bbBar[curBBIdx]->bBarState < 0) bbBar[curBBIdx]->bBarState = 0;
		cout << "bbBar state: " << bbBar[curBBIdx]->bBarState << endl;
	}
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


void GameGUI::ReduceHPBar()
{
	if (hpBar[curHPIdx]->hpBarState == HPBarState::ZERO) curHPIdx--;
	if (curHPIdx < 0) curHPIdx = 0;
	hpBar[curHPIdx]->hpBarState -= 1;
	if (hpBar[curHPIdx]->hpBarState < 0) hpBar[curHPIdx]->hpBarState = 0;
}

void GameGUI::ReduceBBBar()
{
	if (bbBar[curBBIdx]->bBarState == 0) curBBIdx--;
	if (curBBIdx < 0) curBBIdx = 0;
	bbBar[curBBIdx]->bBarState -= 1;
	if (bbBar[curBBIdx]->bBarState < 0) bbBar[curBBIdx]->bBarState = 0;
}

void GameGUI::IncreaseHPBar()
{
	if (hpBar[curHPIdx]->hpBarState == HPBarState::ZERO) {
		hpBar[curHPIdx]->hpBarState += 1;
	}
	else if (hpBar[curHPIdx]->hpBarState == HPBarState::HALF) {
		hpBar[curHPIdx]->hpBarState += 1;
		curHPIdx++;
	}
	if (curHPIdx >= curMaxHPBar) {
		curHPIdx--;
		cout << curHPIdx << endl;
	}
}

void GameGUI::IncreaseBBBar()
{
	if (bbBar[curBBIdx]->bBarState == 0) {
		bbBar[curBBIdx]->bBarState = 1;
		curBBIdx++;
	}
	if (curBBIdx >= curMaxBBBar) curBBIdx--;
}

void GameGUI::IncreaseMoneyBar(int _money)
{
	moneyNum = _money;
}

void GameGUI::IncreaseBoxKeyBar(int _boxKeyNum)
{
	boxKeyNum = _boxKeyNum;
}
