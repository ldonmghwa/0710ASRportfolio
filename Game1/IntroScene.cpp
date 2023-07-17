#include "stdafx.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
	titleImage = new ObImage(L"intro.png");
	titleImage->scale.x = titleImage->imageSize.x / 5.0f * 10.0f;
	titleImage->scale.y = titleImage->imageSize.y / 10.0f * 10.0f;
	titleImage->maxFrame.x = 5;
	titleImage->maxFrame.y = 10;
	titleImage->ChangeAnim(ANIMSTATE::LOOP, 0.1f, false);
}

IntroScene::~IntroScene()
{
	delete titleImage;
	TEXTURE->DeleteTexture(L"intro.png");
}

void IntroScene::Init()
{
	titleImage->SetWorldPos(Vector2(0.0f, 100.0f));
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
	titleImage->Update();
}

void IntroScene::LateUpdate()
{
}

void IntroScene::Render()
{
	titleImage->Render();
}

void IntroScene::ResizeScreen()
{
}
