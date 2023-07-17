#include "stdafx.h"
#include "Main.h"
#include "IntroScene.h"
#include "MainGameScene.h"
#include "Player.h"

Main::Main()
{

}

Main::~Main()
{
}

void Main::Init()
{
	introSc = new IntroScene();
	SCENE->AddScene("INTROSCENE", introSc);

	mainGSc = new MainGameScene();
	SCENE->AddScene("MAINGAMESCENE", mainGSc);

	SCENE->ChangeScene("INTROSCENE");
}

void Main::Release()
{
   
}

void Main::Update()
{
	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1600.0f,1000.0f);
    app.background = Color(0.0, 0.0, 0.0);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}