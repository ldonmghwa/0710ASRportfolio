#include "common.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
	titleImage = new ObImage(L"Intro_10x14.png");
	titleImage->scale.x = titleImage->imageSize.x / 10.0f * 2.5f;
	titleImage->scale.y = titleImage->imageSize.y / 14.0f * 2.2f;
	titleImage->maxFrame.x = 10;
	titleImage->maxFrame.y = 14;
	titleImage->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	titleLogoImage = new ObImage(L"Enter_the_Gungeon_Logo.png");
	titleLogoImage->scale.x = titleImage->imageSize.x / 8.0f ;
	titleLogoImage->scale.y = titleImage->imageSize.y / 18.0f;
	
	playButton = new ObRect();
	playButton->scale.x = 130.0f;
	playButton->scale.y = 50.0f;
	playButton->isVisible = false;

	endButton = new ObRect();
	endButton->scale.x = 130.0f;
	endButton->scale.y = 50.0f;
	endButton->isVisible = false;

	playButton->SetWorldPos(Vector2(-700.0f, -300.0f));
	endButton->SetWorldPos(Vector2(-700.0f, -400.0f));

	introSDkey = "ETGMainTheme";
	SOUND->AddSound("Enter_The_Gungeon_Main_Theme.mp3", introSDkey);
	SOUND->SetVolume(introSDkey, 1.0f);

}

IntroScene::~IntroScene()
{
	delete titleImage;
	delete playButton;
	delete endButton;
	delete titleLogoImage;

	TEXTURE->DeleteTexture(L"Intro_10x14.png");
	TEXTURE->DeleteTexture(L"Enter_the_Gungeon_Logo.png");

	SOUND->DeleteSound(introSDkey);
}

void IntroScene::Init()
{
	titleImage->SetWorldPos(Vector2(0.0f, 100.0f));
	playButtonScale = 0.0f;
	endButtonScale = 0.0f;
}

void IntroScene::Release()
{
}

void IntroScene::Update()
{
	if (INPUT->KeyDown('1'))
	{
		SCENE->ChangeScene("MAINGAMESCENE");
	}
	SOUND->Play(introSDkey);
	titleImage->Update();
	titleLogoImage->Update();
	playButton->Update();
	endButton->Update();
}

void IntroScene::LateUpdate()
{
	if (playButton->Intersect(INPUT->GetWorldMousePos())) {
		playButtonScale = 20.0f;
		if (INPUT->KeyDown(VK_LBUTTON)) SCENE->ChangeScene("MAINGAMESCENE");
	}
	else playButtonScale = 0.0f;

	if (endButton->Intersect(INPUT->GetWorldMousePos())) {
		endButtonScale = 20.0f;
		if (INPUT->KeyDown(VK_LBUTTON)) PostQuitMessage(0);
	}
	else endButtonScale = 0.0f;

	playButton->scale.x = 130.0f + playButtonScale;
	playButton->scale.y = 50.0f + playButtonScale;

	endButton->scale.x = 130.0f + endButtonScale;
	endButton->scale.y = 50.0f + endButtonScale;
}

void IntroScene::Render()
{

	RECT rc2;

	rc2.left = Utility::WorldToScreen(playButton->GetWorldPos()).x - 45.0f - (playButtonScale * 0.7f);
	rc2.top = Utility::WorldToScreen(playButton->GetWorldPos()).y - 15.0f - (playButtonScale * 0.25f);
	rc2.right = rc2.left + 100.0f + playButtonScale * 2.0f;
	rc2.bottom = rc2.top + 50.0f;
	DWRITE->RenderText(L"플레이", rc2, 30.0f + playButtonScale * 0.5f
		, L"둥근모꼴", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_EXPANDED);

	RECT rc1;

	rc1.left = Utility::WorldToScreen(endButton->GetWorldPos()).x - 60.0f - endButtonScale * 0.7f;
	rc1.top = Utility::WorldToScreen(endButton->GetWorldPos()).y - 15.0f - endButtonScale * 0.25f;
	rc1.right = rc1.left + 150.0f + endButtonScale * 2.0f;
	rc1.bottom = rc1.top + 50.0f;
	DWRITE->RenderText(L"게임종료", rc1, 30.0f + endButtonScale * 0.5f
		, L"둥근모꼴", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_EXPANDED);
	titleImage->Render();
	titleLogoImage->Render();
	playButton->Render();
	endButton->Render();
}

void IntroScene::ResizeScreen()
{
}
